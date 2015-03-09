#include<dlfcn.h>
#include<iostream>
#include<string>
#include"pluginManager.hh"
#include"plugin.hh"

using std::cerr;
using std::endl;

int main(int argc, char** argv){
  pluginManager pm;
  plugin* hello;

  pm.registerPlug(std::string("./libHelloPlugin.so"));
  pluginWrapper wrap = pm.getPlugin(std::string("hello"));

  hello = (*wrap.create)();
  hello->run();

  wrap.del(hello);
  return 0;
}

