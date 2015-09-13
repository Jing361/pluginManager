#ifndef __THING_H__
#define __THING_H__

#include"actor.hh"

class thing:public actor{
public:
  virtual ~thing(){  }
  static actor* create();
  static void destroy(actor* obj);
  void run();
};

#endif

