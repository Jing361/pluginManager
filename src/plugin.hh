#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include"pluginManager.hh"

template<class T>
class pluginManager;

template<class T>
class plugin{
public:
  plugin(){  }
  plugin(pluginManager<T>& pm){  }
  virtual ~plugin(){  }
};

#endif

