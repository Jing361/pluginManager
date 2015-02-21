#include"pluginManager.hh"
#include"helloPlugin.hh"

int main(int argc, char** argv){
//  pluginManager pm = new pluginManager;
  helloPlugin pi;
  pi.run();

  return 0;
}

