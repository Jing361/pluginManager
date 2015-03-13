#ifndef __PMDEFS_H__
#define __PMDEFS_H__

#include"plugin.hh"

class plugin;

//TODO:come up with prefix to use with all these types
//       to make it clearer they come from this framework
typedef unsigned char byte_t;

typedef void*(*create_t)();
typedef void(*delete_t)(void*);
typedef char*(*name_t)();

typedef struct{
  unsigned int major;
  unsigned int minor;
}version_t;

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

typedef unsigned int (*registerFunc)(const byte_t* nodeType, const registerParams* params);

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

