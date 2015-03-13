#ifndef __PLUGIN_MANAGER_H__
#define __PLUGIN_MANAGER_H__

#include<map>
#include<vector>
#include<iostream>
#include<dlfcn.h>
#include"pmDefs.hh"

class pluginManager{
private:
  std::map<std::string, pluginWrapper> mapWrapper;
  std::vector<void*> handles;
public:
  pluginManager();
  virtual ~pluginManager();
  void load(const char* dir);
  void load(std::string dir);
  static unsigned int registerObject(const byte_t* name, const registerParams* rp);
  void* createObject(const byte_t* name);
};

#endif

