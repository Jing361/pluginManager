#ifndef __PLUGIN_MANAGER_HH__
#define __PLUGIN_MANAGER_HH__

#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<functional>
#include<dlfcn.h>

#include"fileManager.hh"

template<class T>
class pluginManager{
public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef unsigned char byte_t;

  typedef std::function<pointer()> create_t;
  typedef std::function<void(pointer)> delete_t;
  typedef std::function<char*()> name_t;

  typedef struct{
    unsigned int major;
    unsigned int minor;
    unsigned int maint;
  }version_t;
  typedef struct{
    version_t version;
    create_t create;
    delete_t destroy;
  }registerParams;

  typedef std::function<int(const byte_t*, const registerParams*)> registerFunc;
  typedef struct{
    version_t version;
    registerFunc registerObject;
  }platformServices;

  //Manager calls the initFunc of a plugin,
  //  from which the plugin registers objects.
  typedef void (*initFunc_t)(const platformServices*);

private:
  platformServices services;
  std::map<std::string, const registerParams*> objMap;
  std::vector<std::string> names;
  std::vector<void*> handles;

public:
  pluginManager():
    services( { { 1, 0, 0 }, [this] (const byte_t* name, const registerParams* rp)->int {
      return registerObject(name, rp);
    } } ){
  }

  virtual ~pluginManager(){
    for(auto it = handles.begin(); it != handles.end(); ++it){
      dlclose(*it);
    }
  }

  int load(const std::string& dir){
    //TODO:should use RTLD_NODELETE if libc is ever updated
    //Until then, using RTLD_LAZY
    //void* handle = dlopen(dir, RTLD_NODELETE);
    char* error;
    void* handle = dlopen(dir.c_str(), RTLD_LAZY);

    if(!handle){
      std::cerr << "Failed to open " << dir << std::endl;
      std::cerr << dlerror() << std::endl;

      return -1;
    }

    initFunc_t init = (initFunc_t)dlsym(handle, "initFunc");

    if((error = dlerror()) != 0){
      std::cerr << "Couldn't find initFunc for " << dir << std::endl;
      std::cerr << error << std::endl;

      return -1;
    }

    init(&(services));

    handles.push_back(handle);
    return 0;
  }

  int loadAll(const std::string& dir){
    int count = 0;
    std::vector<std::string> files = fileManager::getFiles(dir);

    for(auto it : files){
      count += load(dir + it);
    }

    return count;
  }

  pointer createObject(const byte_t* name){
    const registerParams* rp = pluginManager<T>::objMap[(const char*)name];
    create_t cr = (create_t)rp->create;

    return (pointer)cr();
  }

  int registerObject(const byte_t* name, const registerParams* rp){
    if(services.version.minor != rp->version.minor){
      return -1;
    }

    objMap.insert(std::pair<std::string, const registerParams*>(std::string((const char*)name), rp));
    names.push_back(std::string((const char*)name));

    return 0;
  }

  std::vector<std::string> getNames(){
    return names;
  }
};

#endif

