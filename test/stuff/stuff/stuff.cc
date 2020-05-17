#include<iostream>
#include"stuff.hh"

actor* stuff::create() {
  return new stuff;
}

void stuff::destroy(actor* obj) {
  if(obj) {
    delete (stuff*) obj;
  }
}

void stuff::run() {
  std::cout << "I'M A STUFF" << std::endl;
}

