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
public:
  typedef unsigned char byte_t;
  typedef std::function<T*()> create_t;
  typedef std::function<void(T*)> delete_t;
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

private:
  platformServices services;
  std::map<std::string, const registerParams*> objMap;
  std::vector<std::string> names;
  std::vector<void*> handles;

public:
  typedef T type;
  //Manager calls the initFunc of a plugin,
  //  from which the plugin registers objects.
  typedef void (*initFunc_t)(const platformServices*);

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

