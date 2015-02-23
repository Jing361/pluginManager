#include"helloPlugin.hh"
#include<iostream>

extern "C"{
plugin* create(){
  return new helloPlugin;
}

void destroy(plugin* pi){
  delete pi;
}

}

helloPlugin::helloPlugin(){
}

helloPlugin::helloPlugin(pluginManager& pm){
}

void helloPlugin::run(){
  std::cout << "HELLO WORLD" << std::endl;
}

