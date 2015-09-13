#include<iostream>
#include"bye.hh"

actor* bye::create(){
  return new bye;
}

void bye::destroy(actor* obj){
  if(obj){
    delete (bye*)obj;
  }
}

void bye::run(){
  std::cout << "I'M AN LGM" << std::endl;
}

