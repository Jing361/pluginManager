#include<string>
#include<iostream>
#include<vector>

#include"pluginManager.hh"
#include"actor.hh"

using namespace std;

int main(){
  typedef pluginManager<actor> mgr;
  mgr pm;
  vector<actor*> actors;

  pm.loadAll("stuff/");

  for( auto name : pm.getNames() ){
    actors.push_back( pm.createObject( ( const mgr::byte_t* ) name.c_str() ) );
  }

  for( auto actr : actors ){
    actr->run();
  }

  return 0;
}

