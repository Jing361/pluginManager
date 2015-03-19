#include<iostream>
#include"stuff.hh"

void* stuff::create(){
  return new stuff;
}

void stuff::destroy(void* obj){
  if(obj){
    delete (stuff*)obj;
  }
}

void stuff::run(){
  std::cout << "I'M A STUFF" << std::endl;
}

