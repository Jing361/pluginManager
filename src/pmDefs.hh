#ifndef __PMDEFS_H__
#define __PMDEFS_H__
//This file is taken from:
//http://www.drdobbs.com/cpp/building-your-own-plugin-framework-part/204202899?pgno=3
//And is the basis for my design of the manager.

//PF in this file stands for plugin framework
 
#ifdef __cplusplus
extern "C" {
#endif

typedef PF_byte_t unsigned char;
 
typedef enum PF_Language
{
  PF_Language_C,
  PF_Language_CPP
} PF_Language;
  
struct PF_PlatformServices;
 
typedef struct PF_ObjectParams
{
  const PF_byte_t * objectType;
  const struct PF_PlatformServices_ * platformServices;
} PF_ObjectParams;
 
typedef struct PF_PluginAPI_Version
{
  unsigned int major;
  unsigned int minor;
} PF_PluginAPI_Version;
 
//Create and destroy implemented by plugin
typedef void * (*PF_CreateFunc)(PF_ObjectParams *);
typedef unsigned int (*PF_DestroyFunc)(void *);
 
typedef struct PF_RegisterParams
{
  PF_PluginAPI_Version version;
  PF_CreateFunc createFunc;
  PF_DestroyFunc destroyFunc;
  PF_ProgrammingLanguage programmingLanguage;
} PF_RegisterParams;
 
//registerfunc implemented by manager
typedef unsigned int (*PF_RegisterFunc)(const PF_byte_t * nodeType, const PF_RegisterParams * params);
typedef unsigned int (*PF_InvokeServiceFunc)(const PF_byte_t * serviceName, void * serviceParams);

typedef struct PF_PlatformServices
{
  PF_PluginAPI_Version version;
  PF_RegisterFunc registerObject;
  PF_InvokeServiceFunc invokeService;
} PF_PlatformServices;
 
//init and exit implemented by plugin
typedef unsigned int (*PF_ExitFunc)();
typedef PF_ExitFunc (*PF_InitFunc)(const PF_PlatformServices *);
 
#ifndef PLUGIN_API
  #ifdef WIN32
    #define PLUGIN_API __declspec(dllimport)
  #else
    #define PLUGIN_API
  #endif
#endif
 
extern
#ifdef  __cplusplus
"C"
#endif
PLUGIN_API PF_ExitFunc PF_initPlugin(const PF_PlatformServices * params);
 
#ifdef  __cplusplus
}
#endif
#endif /* PM_PLUGIN_H */
