
ADD_SUBDIRECTORY(stuff)
ADD_SUBDIRECTORY(thing)

ADD_LIBRARY(StuffPlugin SHARED stuffPlugin.cc)
TARGET_LINK_LIBRARIES(StuffPlugin PluginManager Stuff Thing Actor)
SET_TARGET_PROPERTIES(StuffPlugin PROPERTIES
                      INTERFACE_CXX_STANDARD 20
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)
