#ifndef __STUFF_PLUGIN_H__
#define __STUFF_PLUGIN_H__

#include"plugin.hh"

//TODO:Determine if an actual class is necessary/useful
//  Currently all action is done in a non-class function
class stuffPlugin:public plugin{
public:
  stuffPlugin();
  stuffPlugin(pluginManager& pm);
  virtual ~stuffPlugin();
};

#endif

