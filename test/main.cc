#include<string>
#include<iostream>
#include<vector>

#include"pluginManager.hh"
#include"actor.hh"

using namespace std;

int main() {
  typedef pluginManager<actor> mgr;
  mgr pm;
  vector<actor*> actors;
  vector<string> names;

  pm.loadAll("stuff/");

  pm.getNames(back_inserter(names));

  for(auto name : names) {
    actors.push_back(pm.createObject(name));
  }

  for(auto actr : actors) {
    actr->run();
  }

  return 0;
}

