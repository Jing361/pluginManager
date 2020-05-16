
ADD_SUBDIRECTORY(greet)
ADD_SUBDIRECTORY(stuff)
ADD_SUBDIRECTORY(actor)

ADD_EXECUTABLE(test-plugin main.cc)
TARGET_LINK_LIBRARIES(test-plugin PluginManager GreetPlugin StuffPlugin)
