#ifndef __GREET_PLUGIN_H__
#define __GREET_PLUGIN_H__

#include"plugin.hh"

//TODO:Determine if an actual class is necessary/useful
//  Currently all action is done in a non-class function
class greetPlugin:public plugin{
public:
  greetPlugin();
  greetPlugin(pluginManager& pm);
  virtual ~greetPlugin();
};

#endif

