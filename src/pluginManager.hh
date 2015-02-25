#ifndef __PLUGINMANAGER_H__
#define __PLUGINMANAGER_H__

#include<vector>
#include<string>
#include<iostream>
#include<dlfcn.h>
#include"pmDefs.hh"
#include"plugin.hh"

class plugin;

typedef plugin*(*create_t)();
typedef void(*delete_t)(plugin*);

class pluginWrapper{
public:
  create_t create;
  delete_t del;
};

class pluginManager{
private:
  std::vector<pluginWrapper> vplugin;
public:
  pluginManager();
  void registerPlug(char* plug);
  void registerPlug(std::string plug);
};

#endif

