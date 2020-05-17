#ifndef __HELLO_H__
#define __HELLO_H__

#include"actor.hh"

class hello : public actor {
public:
  virtual ~hello() {
  }

  static actor* create();

  static void destroy(actor* obj);

  void run();
};

#endif

