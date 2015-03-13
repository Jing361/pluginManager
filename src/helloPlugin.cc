#include<iostream>
#include"helloPlugin.hh"
#include"pmDefs.hh"

#include"actor.hh"

extern "C"{

void initFunc(const platformServices* services){
  registerParams* rp = new registerParams;

  rp->version.major = 0;
  rp->version.minor = 1;
  rp->create = &hello::create;
  rp->destroy = &hello::destroy;

//The below lines work.
//  But the function pointer doesn't? so I'm confused.
//actor* actr = (actor*)hello::create();
//actr->run();

  services->registerObject((const byte_t*)"killerBunny", rp);
}

}

helloPlugin::helloPlugin(){  }

helloPlugin::helloPlugin(pluginManager& pm){  }

helloPlugin::~helloPlugin(){  }

