#include<string>
#include<iostream>
#include"pluginManager.hh"
#include"actor.hh"

int main(){
  pluginManager<actor> pm;
  actor* actr1;
  actor* actr2;
  actor* actr3;
  actor* actr4;

  pm.loadAll("stuff/");

  actr1 = pm.createObject((const byte_t*)"killerBunny");
  actr2 = pm.createObject((const byte_t*)"killerLGM");
  actr3 = pm.createObject((const byte_t*)"things");
  actr4 = pm.createObject((const byte_t*)"stuffs");

  actr1->run();
  actr2->run();
  actr3->run();
  actr4->run();
  return 0;
}

