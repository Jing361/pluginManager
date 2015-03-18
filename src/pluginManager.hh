#ifndef __PLUGIN_MANAGER_H__
#define __PLUGIN_MANAGER_H__

#include<map>
#include<vector>
#include<iostream>
#include<dlfcn.h>
#include"pmDefs.hh"

class pluginManager{
private:
  platformServices services;
  std::map<std::string, const registerParams*> objMap;
public:
  pluginManager();
  virtual ~pluginManager();
  void load(const char* dir);
  void load(std::string dir);
  void* createObject(const byte_t* name);
  int registerObject(const byte_t* name, const registerParams* rp);
};

#endif

