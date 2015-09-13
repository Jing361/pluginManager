#ifndef __STUFF_H__
#define __STUFF_H__

#include"actor.hh"

class stuff:public actor{
public:
  virtual ~stuff(){  }
  static actor* create();
  static void destroy(actor* obj);
  void run();
};

#endif

