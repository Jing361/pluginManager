#include<string>
#include<iostream>
#include"pluginManager.hh"

std::map<std::string, const registerParams*> pluginManager::objMap;

pluginManager::pluginManager(){
}

pluginManager::~pluginManager(){
//  for(auto iter = this->handles.begin(); iter != this->handles.end(); ++iter){
//    dlclose(*iter);
//  }
}

void pluginManager::load(const char* dir){
  //TODO:check existence of path and file.
  platformServices services;
  char* error;
  //TODO:should use rtld_nodelete if libc is ever updated
  //void* handle = dlopen(dir, RTLD_NODELETE);
  //until then dlclose must be done somewhere else.
  void* handle = dlopen(dir, RTLD_LAZY);

  services.version.major = 0;
  services.version.minor = 1;
  services.registerObject = pluginManager::registerObject;

  if(!handle){
    std::cerr << "Failed to open " << dir << std::endl;
    std::cerr << dlerror() << std::endl;
    return;
  }

  initFunc_t init = (initFunc_t)dlsym(handle, "initFunc");
  if((error = dlerror()) != 0){
    std::cerr << error << std::endl;
    return;
  }

  init(&services);

  //It is possible we want to close the handle later on around manager destruction
  //dlclose(handle);
}

void pluginManager::load(std::string dir){
  this->load(dir.c_str());
}

unsigned int pluginManager::registerObject(const byte_t* name, const registerParams* rp){
  pluginManager::objMap.insert(std::pair<std::string, const registerParams*>(std::string((const char*)name), rp));
  return 0;
}

void* pluginManager::createObject(const byte_t* name){
  const registerParams* rp = pluginManager::objMap[(const char*)name];
  create_t cr = (create_t)rp->create;
  return cr();
}

