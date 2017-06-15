#include"thing.hh"
#include"stuff.hh"
#include"pluginManager.hh"

template class pluginManager<actor>;

extern "C"{

void initFunc(const pluginManager<actor>::platformServices* services){
  pluginManager<actor>::registerParams* bunnyRP = new pluginManager<actor>::registerParams;
  pluginManager<actor>::registerParams* lgmRP = new pluginManager<actor>::registerParams;

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

  services->registerObject( "things", bunnyRP );

  services->registerObject( "stuffs", lgmRP );
}

}

