#include"helloPlugin.hh"
#include"pmDefs.hh"

extern "C"{

void initFunc(const platformServices* services){
  registerParams* rp = new registerParams;

  rp->version.major = 0;
  rp->version.minor = 2;
  rp->version.maint = 0;
  rp->create = &hello::create;
  rp->destroy = &hello::destroy;

  services->registerObject((const byte_t*)"killerBunny", rp);
}

}

helloPlugin::helloPlugin(){  }

helloPlugin::helloPlugin(pluginManager& pm){  }

helloPlugin::~helloPlugin(){  }

