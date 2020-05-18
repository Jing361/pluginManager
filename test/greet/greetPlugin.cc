#include"bunny/hello.hh"
#include"lgm/bye.hh"
#include"pluginManager.hh"

template
class pluginManager<actor>;

extern "C" {

void initFunc(const pluginManager<actor>::platform_services& services) {
  pluginManager<actor>::registration_parameters bunnyRP;
  pluginManager<actor>::registration_parameters lgmRP;

  bunnyRP.version.major = 1;
  bunnyRP.version.minor = 0;
  bunnyRP.version.maint = 0;
  bunnyRP.create = &hello::create;
  bunnyRP.destroy = &hello::destroy;

  lgmRP.version.major = 1;
  lgmRP.version.minor = 0;
  lgmRP.version.maint = 0;
  lgmRP.create = &bye::create;
  lgmRP.destroy = &bye::destroy;

  services.registerObject("killerBunny", bunnyRP);

  services.registerObject("killerLGM", lgmRP);
}

}

