#include<string>
#include<iostream>
#include"pluginManager.hh"

pluginManager::pluginManager(){
  this->services.version.major = 0;
  this->services.version.minor = 2;
  this->services.version.maint = 0;
  this->services.registerObject = [this] (const byte_t* name, const registerParams* rp)->int { return this->registerObject(name, rp); };
}

pluginManager::~pluginManager(){
//  for(auto iter = this->handles.begin(); iter != this->handles.end(); ++iter){
//    dlclose(*iter);
//  }
}

int pluginManager::load(const char* dir){
  //TODO:check existence of path and file.
  //TODO:should use rtld_nodelete if libc is ever updated
  //void* handle = dlopen(dir, RTLD_NODELETE);
  //TODO:Need to call dlclose appropriately.
  //until then dlclose must be done somewhere else.
  //If dlclose called in this call, program dumps.
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

  //It is possible we want to close the handle later on around manager destruction
  //dlclose(handle);
  return 0;
}

int pluginManager::load(std::string dir){
  return this->load(dir.c_str());
}

int pluginManager::loadall(const char* dir){
  return this->loadAll(std::string(dir));
}

int pluginManager::loadAll(std::string dir){
  std::vector<std::string>* files = this->getFiles(dir);
  int count = 0;

  for(auto it = files->begin(); it != files->end(); ++it){
    count += this->load(*it);
  }
  return count;
}

std::vector<std::string>* pluginManager::getFiles(std::string dir){
  DIR *dp;
  struct dirent *dirp;
  std::vector<std::string>* files = new std::vector<std::string>;

  if((dp  = opendir(dir.c_str())) == NULL) {
    std::cerr << "Error(" << errno << ") opening " << dir << std::endl;
    return 0;
  }

  while ((dirp = readdir(dp)) != NULL) {
    files->push_back(std::string(dirp->d_name));
  }

  closedir(dp);
  return files;
}

int pluginManager::registerObject(const byte_t* name, const registerParams* rp){
//TODO:add version checking...
//Use lambdas..?
  //Incompatible version check.
  if(this->services.version.minor != rp->version.minor){
    return -1;
  }
  this->objMap.insert(std::pair<std::string, const registerParams*>(std::string((const char*)name), rp));
  return 0;
}

void* pluginManager::createObject(const byte_t* name){
  const registerParams* rp = pluginManager::objMap[(const char*)name];
  create_t cr = (create_t)rp->create;
  return cr();
}

void pluginManager::test(){
  for(auto it = this->objMap.begin(); it != this->objMap.end(); ++it){
    std::cout << it->first << '\t' << it->second << std::endl;
  }
}

