#ifndef __PMDEFS_H__
#define __PMDEFS_H__

#include<functional>
#include"plugin.hh"

//template<class T>
//class plugin;

//TODO:come up with prefix to use with all these types
//       to make it clearer they come from this framework
typedef unsigned char byte_t;

typedef std::function<void*()> create_t;
typedef std::function<void(void*)> delete_t;
typedef std::function<char*()> name_t;

typedef struct{
  unsigned int major;
  unsigned int minor;
  unsigned int maint;
}version_t;

//I'm not confident in the difference between pluginwrapper and registerparams right now.
typedef struct{
  version_t version;
  create_t create;
  delete_t del;
  std::string name;
}pluginWrapper;

//Provided by plugin to register object.
typedef struct{
  version_t version;
  create_t create;
  delete_t destroy;
}registerParams;

typedef std::function<int(const byte_t*, const registerParams*)> registerFunc;

//Things provided by manager.
//Including:
//  the managers version, to ensure version compatability
//  method for plugin to register objects
typedef struct{
  version_t version;
  registerFunc registerObject;
}platformServices;

//Manager calls the initFunc of a plugin, from which the plugin registers objects.
typedef void (*initFunc_t)(const platformServices*);

#endif

