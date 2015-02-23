#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include"pmDefs.hh"

class plugin{
private:
  PF_PluginAPI_Version version;
public:
  virtual void run();
};

#endif

