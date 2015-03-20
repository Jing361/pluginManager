#include"pmDefs.hh"
#include"hello.hh"
#include"bye.hh"

extern "C"{

void initFunc(const platformServices* services){
  registerParams* bunnyRP = new registerParams;
  registerParams* lgmRP = new registerParams;

  bunnyRP->version.major = 1;
  bunnyRP->version.minor = 0;
  bunnyRP->version.maint = 0;
  bunnyRP->create = &hello::create;
  bunnyRP->destroy = &hello::destroy;

  lgmRP->version.major = 1;
  lgmRP->version.minor = 0;
  lgmRP->version.maint = 0;
  lgmRP->create = &bye::create;
  lgmRP->destroy = &bye::destroy;

  services->registerObject((const byte_t*)"killerBunny", bunnyRP);

  services->registerObject((const byte_t*)"killerLGM", lgmRP);
}

}

