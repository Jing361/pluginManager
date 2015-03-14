#ifndef __HELLO_PLUGIN_H__
#define __HELLO_PLUGIN_H__

#include"plugin.hh"
#include"hello.hh"

//TODO:Determine if an actual class is necessary/useful
//  Currently all action is done in a non-class function
class helloPlugin:public plugin{
public:
  helloPlugin();
  helloPlugin(pluginManager& pm);
  virtual ~helloPlugin();
};

#endif

