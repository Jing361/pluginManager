#include"hello.hh"
#include"bye.hh"
#include"pluginManager.hh"

template class pluginManager<actor>;

extern "C"{

void initFunc(const pluginManager<actor>::platformServices* services){
  pluginManager<actor>::registerParams* bunnyRP = new pluginManager<actor>::registerParams;
  pluginManager<actor>::registerParams* lgmRP = new pluginManager<actor>::registerParams;

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

  services->registerObject( "killerBunny", bunnyRP );

  services->registerObject( "killerLGM", lgmRP );
}

}

