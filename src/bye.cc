#include<iostream>
#include"bye.hh"

void* bye::create(){
  return new bye;
}

void bye::destroy(void* obj){
  if(obj){
    delete (bye*)obj;
  }
}

void bye::run(){
  std::cout << "I'M AN LGM" << std::endl;
}

