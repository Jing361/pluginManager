#ifndef __THING_H__
#define __THING_H__

#include"actor.hh"

class thing:public actor{
public:
  virtual ~thing(){  }
  static void* create();
  static void destroy(void* obj);
  void run();
};

#endif

