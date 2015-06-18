#include<string>
#include<iostream>
#include"fileManager.hh"

template<class T>
pluginManager<T>::pluginManager(){
  this->services.version.major = 1;
  this->services.version.minor = 0;
  this->services.version.maint = 0;
  this->services.registerObject = [this] (const byte_t* name, const registerParams* rp)->int { return this->registerObject(name, rp); };
}

template<class T>
pluginManager<T>::~pluginManager(){
  for(auto it = this->handles.begin(); it != this->handles.end(); ++it){
    dlclose(*it);
  }
}

template<class T>
int pluginManager<T>::load(const char* dir){
  //TODO:should use RTLD_NODELETE if libc is ever updated
  //Until then, using RTLD_LAZY
  //void* handle = dlopen(dir, RTLD_NODELETE);
  char* error;
  void* handle = dlopen(dir, RTLD_LAZY);

  if(!handle){
    std::cerr << "Failed to open " << dir << std::endl;
    std::cerr << dlerror() << std::endl;
    return -1;
  }

  initFunc_t init = (initFunc_t)dlsym(handle, "initFunc");
  if((error = dlerror()) != 0){
    std::cerr << "Couldn't find initFunc for " << dir << std::endl;
    std::cerr << error << std::endl;
    return -1;
  }

  init(&(this->services));

  handles.push_back(handle);
  //dlclose(handle);
  return 0;
}

template<class T>
int pluginManager<T>::load(std::string dir){
  return this->load(dir.c_str());
}

template<class T>
int pluginManager<T>::loadall(const char* dir){
  return this->loadAll(std::string(dir));
}

template<class T>
int pluginManager<T>::loadAll(std::string dir){
  std::vector<std::string>* files = fileManager::getFiles(dir);
  int count = 0;

  for(auto it = files->begin(); it != files->end(); ++it){
    count += this->load(dir + *it);
  }
  return count;
}

template<class T>
int pluginManager<T>::registerObject(const byte_t* name, const registerParams* rp){
  if(this->services.version.minor != rp->version.minor){
    return -1;
  }
  this->objMap.insert(std::pair<std::string, const registerParams*>(std::string((const char*)name), rp));
  return 0;
}

template<class T>
T* pluginManager<T>::createObject(const byte_t* name){
  const registerParams* rp = pluginManager<T>::objMap[(const char*)name];
  create_t cr = (create_t)rp->create;
  return (T*)cr();
}

