#ifndef __BYE_H__
#define __BYE_H__

#include"actor.hh"

class bye : public actor {
public:
  virtual ~bye() {
  }

  static actor* create();

  static void destroy(actor* obj);

  void run();
};

#endif

