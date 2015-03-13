#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include"pluginManager.hh"

class pluginManager;

class plugin{
public:
  plugin(){  }
  plugin(pluginManager& pm){  }
  virtual ~plugin(){  }
};

#endif

