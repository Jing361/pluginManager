#ifndef __BYE_H__
#define __BYE_H__

#include"actor.hh"

class bye:public actor{
public:
  virtual ~bye(){  }
  static void* create();
  static void destroy(void* obj);
  void run();
};

#endif

