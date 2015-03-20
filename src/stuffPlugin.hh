#ifndef __STUFF_PLUGIN_H__
#define __STUFF_PLUGIN_H__

#include"plugin.hh"
#include"actor.hh"

//TODO:Determine if an actual class is necessary/useful
//  Currently all action is done in a non-class function
class stuffPlugin:public plugin<actor>{
public:
  stuffPlugin();
  stuffPlugin(pluginManager<actor>& pm);
  virtual ~stuffPlugin();
};

#endif

