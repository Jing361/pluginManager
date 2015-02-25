#include"pluginManager.hh"

pluginManager::pluginManager(){
}

void pluginManager::registerPlug(std::string plug){
  this->registerPlug(plug.c_str());
}

void pluginManager::registerPlug(char* plug){
  void* handle = dlopen(plug, RTLD_LAZY);
  char* error;
  pluginWrapper wrap;

  if(!handle){
    std::cerr << dlerror() << std::endl;
    return;
  }
  wrap.create = (create_t)dlsym(handle, "create");
  if((error = dlerror()) != 0){
    std::cerr << error << std::endl;
    return;
  }
  wrap.del = (delete_t)dlsym(handle, "destroy");
  if((error = dlerror()) != 0){
    std::cerr << error << std::endl;
    return;
  }
  name_t nam = (name_t)dlsym(handle, "name");
  if((error = dlerror()) != 0){
    std::cerr << error << std::endl;
    return;
  }
  wrap.name = (*nam)();
  //It is possible we want to close the handle later on around manager destruction
  dlclose(handle);

  mplugin.insert(std::pair<std::string, pluginWrapper>(wrap.name, wrap));
}

