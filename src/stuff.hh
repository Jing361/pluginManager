#ifndef __STUFF_H__
#define __STUFF_H__

#include"actor.hh"

class stuff:public actor{
public:
  virtual ~stuff(){  }
  static void* create();
  static void destroy(void* obj);
  void run();
};

#endif

