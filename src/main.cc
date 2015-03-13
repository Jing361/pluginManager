#include<string>
#include<iostream>
#include"pluginManager.hh"
#include"actor.hh"

int main(int argc, char** argv){
  pluginManager pm;
  actor* actr;

  pm.load("libHelloPlugin.so");
  actr = (actor*)pm.createObject((const byte_t*)"killerBunny");
  actr->run();
  return 0;
}

