ADD_SUBDIRECTORY(bunny)
ADD_SUBDIRECTORY(lgm)

ADD_LIBRARY(GreetPlugin greetPlugin.cc)
TARGET_LINK_LIBRARIES(GreetPlugin PluginManager BUNNY LGM Actor)
