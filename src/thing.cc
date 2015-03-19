#include<iostream>
#include"thing.hh"

void* thing::create(){
  return new thing;
}

void thing::destroy(void* obj){
  if(obj){
    delete (thing*)obj;
  }
}

void thing::run(){
  std::cout << "I'M A THING" << std::endl;
}

