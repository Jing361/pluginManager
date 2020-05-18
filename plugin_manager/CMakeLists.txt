
ADD_SUBDIRECTORY(file_manager)

ADD_LIBRARY(PluginManager INTERFACE)
TARGET_INCLUDE_DIRECTORIES(PluginManager INTERFACE header)
TARGET_LINK_LIBRARIES(PluginManager
                      INTERFACE FileManager
                      INTERFACE ${CMAKE_DL_LIBS})
SET_TARGET_PROPERTIES(PluginManager PROPERTIES
                      INTERFACE_CXX_STANDARD 20
                      INTERFACE_CXX_STANDARD_REQUIRED YES
                      INTERFACE_CXX_EXTENSIONS NO)

