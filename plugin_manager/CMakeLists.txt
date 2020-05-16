
ADD_SUBDIRECTORY(file_manager)

ADD_LIBRARY(PluginManager INTERFACE)
TARGET_INCLUDE_DIRECTORIES(PluginManager INTERFACE header)
TARGET_LINK_LIBRARIES(PluginManager
                      INTERFACE FileManager
                      INTERFACE ${CMAKE_DL_LIBS})
