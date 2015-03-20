#include"pmDefs.hh"
#include"thing.hh"
#include"stuff.hh"

extern "C"{

void initFunc(const platformServices* services){
  registerParams* bunnyRP = new registerParams;
  registerParams* lgmRP = new registerParams;

  bunnyRP->version.major = 1;
  bunnyRP->version.minor = 0;
  bunnyRP->version.maint = 0;
  bunnyRP->create = &thing::create;
  bunnyRP->destroy = &thing::destroy;

  lgmRP->version.major = 1;
  lgmRP->version.minor = 0;
  lgmRP->version.maint = 0;
  lgmRP->create = &stuff::create;
  lgmRP->destroy = &stuff::destroy;

  services->registerObject((const byte_t*)"things", bunnyRP);

  services->registerObject((const byte_t*)"stuffs", lgmRP);
}

}

