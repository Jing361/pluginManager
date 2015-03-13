#include<string>
#include<iostream>
#include"pluginManager.hh"
#include"actor.hh"

int main(int argc, char** argv){
std::cout << "Running!" << std::endl;
  pluginManager pm;
  actor* actr;

std::cout << "Loading!" << std::endl;
  pm.load("libHelloPlugin.so");
std::cout << "Creating!" << std::endl;
  actr = (actor*)pm.createObject((const byte_t*)"killerBunny");
std::cout << "Running!" << std::endl;
  actr->run();
std::cout << "Closing!" << std::endl;
  return 0;
}

