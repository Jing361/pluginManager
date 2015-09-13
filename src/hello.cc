#include<iostream>
#include"hello.hh"

actor* hello::create(){
  return new hello;
}

void hello::destroy(actor* obj){
  if(obj){
    delete (hello*)obj;
  }
}

void hello::run(){
  std::cout << "I'M A BUNNY" << std::endl;
}

