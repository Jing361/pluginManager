#ifndef __HELLO_PLUGIN_H__
#define __HELLO_PLUGIN_H__

#include"plugin.hh"
#include"hello.hh"

class helloPlugin:public plugin{
public:
  helloPlugin();
  helloPlugin(pluginManager& pm);
  virtual ~helloPlugin();
};

#endif

