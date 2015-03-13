#include<iostream>
#include"hello.hh"

void* hello::create(){
  return new hello;
}

void hello::destroy(void* obj){
  if(obj){
    delete (hello*)obj;
  }
}

void hello::run(){
  std::cout << "I'M A BUNNY" << std::endl;
}

