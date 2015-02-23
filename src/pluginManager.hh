#ifndef __PLUGINMANAGER_H__
#define __PLUGINMANAGER_H__

#include<vector>
#include<string>
#include<dlfcn.h>
#include"pmDefs.hh"
#include"plugin.hh"

class plugin;

class pluginManager{
private:
  std::vector<plugin> vplugin;
  void* handle;
public:
  pluginManager();
  pluginManager(char* dir);
  pluginManager(std::string dir);
  void registerPlug(plugin& plug);
};

#endif

