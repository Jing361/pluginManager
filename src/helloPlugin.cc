#include<iostream>
#include"helloPlugin.hh"
#include"pmDefs.hh"

extern "C"{

void initFunc(const platformServices* services){
  registerParams rp;

  rp.version.major = 0;
  rp.version.minor = 1;
  rp.create = hello::create;
  rp.destroy = hello::destroy;

  services->registerObject((const byte_t*)"helloBunny", &rp);
}

}

helloPlugin::helloPlugin(){  }

helloPlugin::helloPlugin(pluginManager& pm){  }

helloPlugin::~helloPlugin(){  }

void helloPlugin::run(){
  std::cout << "hello!!" << std::endl;
}

