#include"pluginManager.hh"

pluginManager::pluginManager(){
}

pluginManager::pluginManager(char* dir):pluginManager(std::string(dir)){
}

pluginManager::pluginManager(std::string dir){
}

void pluginManager::registerPlug(plugin& plug){
  this->vplugin.push_back(plug);
}

