#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include"pmDefs.hh"

class plugin{
protected:
  PF_PluginAPI_Version version;
public:
  //Must have empty brackets for it to compile.
  virtual void run(){  }
  virtual ~plugin(){  }
};

#endif

