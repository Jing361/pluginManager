#ifndef __HELLOPLUGIN_H__
#define __HELLOPLUGIN_H__

#include"plugin.hh"

class helloPlugin:public plugin{
public:
  helloPlugin();
  helloPlugin(pluginManager& pm);
  void run();
};

#endif

