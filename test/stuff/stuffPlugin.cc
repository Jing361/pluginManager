#include"thing/thing.hh"
#include"stuff/stuff.hh"
#include<pluginManager.hh>

template
class pluginManager<actor>;

extern "C" {

void initFunc(const pluginManager<actor>::platform_services& services) {
  pluginManager<actor>::registration_parameters bunnyRP;
  pluginManager<actor>::registration_parameters lgmRP;

  bunnyRP.version.major = 1;
  bunnyRP.version.minor = 0;
  bunnyRP.version.maint = 0;
  bunnyRP.create = &thing::create;
  bunnyRP.destroy = &thing::destroy;

  lgmRP.version.major = 1;
  lgmRP.version.minor = 0;
  lgmRP.version.maint = 0;
  lgmRP.create = &stuff::create;
  lgmRP.destroy = &stuff::destroy;

  services.registerObject("things", bunnyRP);

  services.registerObject("stuffs", lgmRP);
}

}

