#ifndef __PLUGINMANAGER_H__
#define __PLUGINMANAGER_H__

#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<dlfcn.h>
#include"pmDefs.hh"
#include"plugin.hh"

class plugin;

typedef plugin*(*create_t)();
typedef void(*delete_t)(plugin*);
typedef char*(*name_t)();

class pluginWrapper{
public:
  create_t create;
  delete_t del;
  std::string name;
};

class pluginManager{
private:
  std::map<std::string, pluginWrapper> mplugin;
public:
  pluginManager();
  void registerPlug(char* plug);
  void registerPlug(std::string plug);
};

#endif

