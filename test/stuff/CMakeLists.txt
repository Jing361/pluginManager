
ADD_SUBDIRECTORY(stuff)
ADD_SUBDIRECTORY(thing)

ADD_LIBRARY(StuffPlugin stuffPlugin.cc)
TARGET_LINK_LIBRARIES(StuffPlugin PluginManager Stuff Thing Actor)
