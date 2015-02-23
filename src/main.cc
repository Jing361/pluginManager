#include<dlfcn.h>
#include<iostream>
#include"plugin.hh"

using std::cerr;
using std::endl;

int main(int argc, char** argv){
  void* handle;
  typedef plugin*(*create_t)();
  typedef void(*delete_t)(plugin*);
  create_t create;
  delete_t del;
  char* error;

  handle = dlopen("./libHelloPlugin.so", RTLD_LAZY);
  if(!handle){
    cerr << dlerror() << endl;
    return 1;
  }

  create = (create_t)dlsym(handle, "create");
  if((error = dlerror()) != 0){
    cerr << error << endl;
    return 1;
  }
  del = (delete_t)dlsym(handle, "destroy");
  if((error = dlerror()) != 0){
    cerr << error << endl;
    return 0;
  }

  plugin *pi;
  pi = (*create)();
  pi->run();

  (*del)(pi);
  dlclose(handle);
  return 0;
}

