#include<string>
#include<iostream>
#include"pluginManager.hh"
#include"actor.hh"

int main(int argc, char** argv){
  pluginManager pm;
  actor* actr1;
  actor* actr2;
  actor* actr3;
  actor* actr4;

//  pm.load("stuff/libGreetPlugin.so");
//  pm.load("stuff/libStuffPlugin.so");
  pm.loadAll("stuff/");

  actr1 = (actor*)pm.createObject((const byte_t*)"killerBunny");
  actr2 = (actor*)pm.createObject((const byte_t*)"killerLGM");
  actr3 = (actor*)pm.createObject((const byte_t*)"things");
  actr4 = (actor*)pm.createObject((const byte_t*)"stuffs");

  actr1->run();
  actr2->run();
  actr3->run();
  actr4->run();
  return 0;
}

