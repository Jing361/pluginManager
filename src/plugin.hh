#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include"pluginManager.hh"
#include"pmDefs.hh"

class pluginManager;

class plugin{
protected:
  PF_PluginAPI_Version version;
public:
  //Must have empty brackets in order to compile
  plugin(){  }
  plugin(pluginManager& pm){  }
  virtual ~plugin(){  }
  virtual void run(){  }
};

#endif

