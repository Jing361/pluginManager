#include<string>
#include<iostream>
#include"pluginManager.hh"
#include"actor.hh"

int main(int argc, char** argv){
std::cout << "Running!" << std::endl;
  pluginManager pm;
  actor* actr;

  pm.load("libHelloPlugin.so");
  actr = (actor*)pm.createObject((const byte_t*)"killerBunny");
  actr->run();
std::cout << "Closing!" << std::endl;
  return 0;
}

