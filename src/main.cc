#include<string>
#include<iostream>
#include"pluginManager.hh"
#include"actor.hh"

int main(int argc, char** argv){
  pluginManager pm;
  actor* actr1;
  actor* actr2;

  pm.load("stuff/libGreetPlugin.so");
  actr1 = (actor*)pm.createObject((const byte_t*)"killerBunny");
  actr2 = (actor*)pm.createObject((const byte_t*)"killerLGM");

  actr1->run();
  actr2->run();
  return 0;
}

