#ifndef __HELLO_H__
#define __HELLO_H__

#include"actor.hh"

class hello:public actor{
public:
  virtual ~hello(){  }
  static void* create();
  static void destroy(void* obj);
  void run();
};

#endif

