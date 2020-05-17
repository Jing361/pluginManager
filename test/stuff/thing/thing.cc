#include<iostream>
#include"thing.hh"

actor* thing::create() {
  return new thing;
}

void thing::destroy(actor* obj) {
  if(obj) {
    delete (thing*) obj;
  }
}

void thing::run() {
  std::cout << "I'M A THING" << std::endl;
}

