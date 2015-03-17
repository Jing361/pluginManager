#include<string>
#include<iostream>
#include"pluginManager.hh"

std::map<std::string, const registerParams*> pluginManager::objMap;

pluginManager::pluginManager(){
  this->services.version.major = 0;
  this->services.version.minor = 1;
  this->services.version.maint = 0;
  this->services.registerObject = pluginManager::registerObject;
}

pluginManager::~pluginManager(){
//  for(auto iter = this->handles.begin(); iter != this->handles.end(); ++iter){
//    dlclose(*iter);
//  }
}

void pluginManager::load(const char* dir){
  //TODO:check existence of path and file.
  char* error;
  //TODO:should use rtld_nodelete if libc is ever updated
  //void* handle = dlopen(dir, RTLD_NODELETE);
  //until then dlclose must be done somewhere else.
  void* handle = dlopen(dir, RTLD_LAZY);

  this->services.version.major = 0;
  this->services.version.minor = 1;
  this->services.version.maint = 0;
  this->services.registerObject = pluginManager::registerObject;

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

  init(&(this->services));

  //It is possible we want to close the handle later on around manager destruction
  //dlclose(handle);
}

void pluginManager::load(std::string dir){
  this->load(dir.c_str());
}

int pluginManager::registerObject(const byte_t* name, const registerParams* rp){
//TODO:add version checking...
//Use lambdas..?
  //Incompatible version check.
//  if(this->services.minor != rp.version.minor){
//    return -1;
//  }
  pluginManager::objMap.insert(std::pair<std::string, const registerParams*>(std::string((const char*)name), rp));
  return 0;
}

void* pluginManager::createObject(const byte_t* name){
  const registerParams* rp = pluginManager::objMap[(const char*)name];
  create_t cr = (create_t)rp->create;
  return cr();
}

