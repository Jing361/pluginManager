#ifndef __PLUGIN_MANAGER_HH__
#define __PLUGIN_MANAGER_HH__

#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<functional>
#include<exception>
#include<dlfcn.h>

#include"fileManager.hh"

struct version_t{
  unsigned int major;
  unsigned int minor;
  unsigned int maint;

#if __cpp_impl_three_way_comparison
  auto operator<=>(const version_t&) const = default;
#else
  bool operator<(const version_t& other) const{
    if(major < other.major) {
      return true;
    } else if(minor < other.minor){
      return true;
    } else {
      return maint < other.maint;
    }
  }

  bool operator==(const version_t& other) const{
    return major == other.major and minor == other.minor and maint == other.maint;
  }

  bool operator!=(const version_t& other) const{
    return !((*this) == other);
  }

  bool operator<=(const version_t& other) const{
    return (*this) < other || (*this) == other;
  }

  bool operator>(const version_t& other) const{
    return !((*this) <= other);
  }

  bool operator>=(const version_t& other) const{
    return !((*this) < other);
  }
#endif
};

//! @todo change to use gsw::exception
class incompatibleVersionException : public std::exception {
private:
  std::string mMesg;

public:
  incompatibleVersionException(const version_t& requested, const version_t& actual)
          : mMesg(
          "The requested version (" + std::to_string(requested.major) + "." + std::to_string(requested.minor) + "." +
          std::to_string(requested.maint) + ") " + "is not compatible with the system version (" +
          std::to_string(actual.major) + "." + std::to_string(actual.minor) + "." + std::to_string(actual.maint) +
          ").") {
  }

  virtual const char* what() const noexcept override {
    return mMesg.c_str();
  }
};

//! @todo change to use gsw::exception
class libraryException : public std::exception {
private:
  std::string mMesg;

public:
  libraryException(const std::string& message)
          : mMesg(message) {
  }

  virtual const char* what() const noexcept override {
    return mMesg.c_str();
  }
};

template<class T>
class pluginManager {
public:
  using value_type = T;
  using pointer = value_type*;
  using reference = value_type&;
  using byte_t = unsigned char;
  using handle_t = void*;

  using create_t = std::function<pointer(void)>;
  using delete_t = std::function<void(pointer)>;
  using name_t = std::function<std::string(void)>;

  struct registration_parameters {
    version_t version;
    create_t create;
    delete_t destroy;
  };

  using registrar = std::function<int(const std::string&, const registration_parameters&)>;

  struct platform_services {
    version_t version;
    registrar registerObject;
  };

private:
  platform_services mServices;
  std::map<std::string, registration_parameters> mObjMap;
  std::vector<handle_t> mHandles;

public:
  /*! Default ctor
   *
   * Initializes platform services struct with version data, and registration
   * callback.
   */
  pluginManager()
          : mServices({{ 1, 0, 0 }, [this](const std::string& name, const registration_parameters& rp) -> int
    {
      return registerObject(name, rp);
    }}) {
  }

  /*! No copy ctor
   *
   * The copy ctor can't exist because it would put handles at risk of being
   * double closed/deleted.  This would of course cause a segfault.
   */
  pluginManager(const pluginManager&) = delete;

  /*! Move ctor
   *
   * @param pm  Manager instance to be moved
   *
   * Move resources out of this instance.
   */
  pluginManager(pluginManager&& pm) {
    mServices.version.major = 0;
    mServices.version.minor = 0;
    mServices.version.maint = 0;

    mServices = pm.mServices;
    mObjMap = std::move(pm.mObjMap);
    mHandles = std::move(pm.mHandles);
  }

  /*! Dtor
   *
   * Close open library handles
   */
  virtual ~pluginManager() {
    for(auto it : mHandles) {
      dlclose(it);
    }
  }

  /*! Load a library into memory
   *
   * @param libName  Name of library to be loaded
   *
   * Load a library, and save a handle_t to it.  This handle_t is used for closing
   * the library in the future.  Also an initialization function is called to
   * load the library itself.  This loading includes registering object types
   * with the plugin manager.
   */
  void load(const std::string& libName) {
    typedef void (*init_ptr)(const platform_services&);

    handle_t hndl = dlopen(libName.c_str(), RTLD_NODELETE);

    if(!hndl) {
      throw libraryException("Failed to open " + std::string(dlerror()));
    }

    auto init = (init_ptr) dlsym(hndl, "initFunc");

    if(const char* error = dlerror(); error != nullptr) {
      throw libraryException("Couldn't find initFunc for " + std::string(error));
    }

    if(init == nullptr){
      throw libraryException("Invalid handle for initFunc symbol");
    }

    init(mServices);

    mHandles.push_back(hndl);
  }

  /*! Load all libraries in a given directory
   *
   * @param dir  Directory to search for libraries
   *
   * Search directory dir for libraries to open, and load them individually.
   */
  int loadAll(const std::string& dir) {
    int count = 0;
    std::vector<std::string> files = fileManager::getFiles(dir);

    for(auto it : files) {
      try {
        load(dir + it);
        ++count;
      } catch(std::exception&) {
        //If it fails, don't count it, move along
      }
    }

    return count;
  }

  /*! Create an instance of a registered object
   *
   * @param name  Name of the object type to be instantiated
   *
   * Using name, find an object to be created.  The instance is generated using
   * the registered function for the object of the given name.
   */
  pointer createObject(const std::string& name) {
    const registration_parameters& rp = mObjMap.at(name);
    create_t cr = rp.create;

    return (pointer) cr();
  }

  /*! Object registration callback
   *
   * @param name  Name of object, to be used again later for creation
   *
   * @param rp  Parameters library registers with; allow for object creation etc
   *
   * Registration point to tell the manager about a creatable object type.
   */
  int registerObject(const std::string& name, const registration_parameters& rp) {
    if(mServices.version.minor <= rp.version.minor) {
      throw incompatibleVersionException(rp.version, mServices.version);
    }

    mObjMap[name] = rp;

    return 0;
  }

  /*! Saves the names of all registered object names
   *
   * @tparam outputIter  Output iterator type
   *
   * @param start  Starting point to enter object names
   *
   * Adds object names through a given output iterator.
   */
  template<typename outputIter>
  void getNames(outputIter start) {
    for(auto it : mObjMap) {
      *start = it.first;
      ++start;
    }
  }
};

#endif

