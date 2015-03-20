#ifndef __GREET_PLUGIN_H__
#define __GREET_PLUGIN_H__

#include"plugin.hh"
#include"actor.hh"

//TODO:Determine if an actual class is necessary/useful
//  Currently all action is done in a non-class function
class greetPlugin:public plugin<actor>{
public:
  greetPlugin();
  greetPlugin(pluginManager<actor>& pm);
  virtual ~greetPlugin();
};

#endif

