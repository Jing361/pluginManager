#ifndef __PLUGIN_MANAGER_H__
#define __PLUGIN_MANAGER_H__

#include<map>
#include<vector>
#include<iostream>
#include<dlfcn.h>
#include<dirent.h>
#include"pmDefs.hh"

class pluginManager{
private:
  platformServices services;
  std::map<std::string, const registerParams*> objMap;
  std::vector<std::string>* getFiles(std::string dir);
public:
  pluginManager();
  virtual ~pluginManager();
  int load(const char* dir);
  int load(std::string dir);
  int loadall(const char* dir);
  int loadAll(std::string dir);
  void* createObject(const byte_t* name);
  int registerObject(const byte_t* name, const registerParams* rp);
};

#endif

