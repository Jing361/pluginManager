#ifndef __PLUGIN_MANAGER_HH__
#define __PLUGIN_MANAGER_HH__

#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<functional>
#include<dlfcn.h>

template<class T>
class pluginManager{
private:
  platformServices services;
  std::map<std::string, const registerParams*> objMap;
  std::vector<std::string> names;
  std::vector<void*> handles;

public:
  typedef T type;
  typedef unsigned char byte_t;
  typedef std::function<T*()> create_t;
  typedef std::function<void(T*)> delete_t;
  typedef std::function<char*()> name_t;
  //Provided by plugin to register object.
  typedef struct{
    version_t version;
    create_t create;
    delete_t destroy;
  }registerParams;
  //Manager calls the initFunc of a plugin,
  //  from which the plugin registers objects.
  typedef void (*initFunc_t)(const platformServices*);
  typedef struct{
    version_t version;
    registerFunc registerObject;
  }platformServices;
  typedef struct{
    unsigned int major;
    unsigned int minor;
    unsigned int maint;
  }version_t;
  typedef std::function<int(const byte_t*, const registerParams*)> registerFunc;

  pluginManager();
  virtual ~pluginManager();

  int load(const char* dir);
  int load(std::string dir);
  int loadall(const char* dir);
  int loadAll(std::string dir);
  T* createObject(const byte_t* name);
  int registerObject(const byte_t* name, const registerParams* rp);
  std::vector<std::string> getNames();
};

#include"pluginManager.cc"

#endif

