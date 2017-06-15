#ifndef __PLUGIN_MANAGER_HH__
#define __PLUGIN_MANAGER_HH__

#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<functional>
#include<exception>
#include<dlfcn.h>

#include"fileManager.hh"

typedef struct{
  unsigned int major;
  unsigned int minor;
  unsigned int maint;
}version_t;


class incompatibleVersionException : public std::exception{
private:
  std::string mMesg;

public:
  incompatibleVersionException( const version_t& requested, const version_t& actual ):
    mMesg( "The requested version (" + std::to_string( requested.major ) + "." +
                                       std::to_string( requested.minor ) + "." +
                                       std::to_string( requested.maint ) + ") " +
           "is not compatible with the system version (" + std::to_string( actual.major ) + "." +
                                                           std::to_string( actual.minor ) + "." +
                                                           std::to_string( actual.maint ) + ")." ){
  }

  virtual const char* what() const noexcept{
    return mMesg.c_str();
  }
};

class libraryException : public std::exception{
private:
  std::string mMesg;

public:
  libraryException( const std::string& message):
    mMesg( message ){
  }

  virtual const char* what() const noexcept{
    return mMesg.c_str();
  }
};

template<class T>
class pluginManager{
public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef unsigned char byte_t;
  typedef void* handle;

  typedef std::function<pointer()> create_t;
  typedef std::function<void( pointer )> delete_t;
  typedef std::function<char*()> name_t;

  typedef struct{
    version_t version;
    create_t create;
    delete_t destroy;
  }registerParams;

  typedef std::function<int( const std::string&, const registerParams* )> registerFunc;

  typedef struct{
    version_t version;
    registerFunc registerObject;
  }platformServices;

  //Manager calls the initFunc of a plugin,
  //  from which the plugin registers objects.
  typedef void ( *initFunc_t )( const platformServices* );

private:
  platformServices mServices;
  std::map<std::string, const registerParams*> mObjMap;
  std::vector<handle> mHandles;

public:
  pluginManager():
    mServices(  { { 1, 0, 0 }, [this]( const std::string& name, const registerParams* rp )->int{
      return registerObject( name, rp );
    } } ){
  }

  virtual ~pluginManager(){
    for( auto it = mHandles.begin(); it != mHandles.end(); ++it ){
      dlclose( *it );
    }
  }

  void load( const std::string& dir ){
    //TODO:should use RTLD_NODELETE if libc is ever updated
    //Until then, using RTLD_LAZY
    //void* handle = dlopen( dir, RTLD_NODELETE );
    char* error;
    void* hndl = dlopen( dir.c_str(), RTLD_LAZY );

    if( !hndl ){
      throw libraryException( "Failed to open " + std::string( dlerror() ) );
    }

    initFunc_t init = ( initFunc_t )dlsym( hndl, "initFunc" );

    if( ( error = dlerror() ) != 0 ){
      throw libraryException( "Couldn't find initFunc for " + std::string( error ) );
    }

    init( &( mServices ) );

    mHandles.push_back( hndl );
  }

  int loadAll( const std::string& dir ){
    int count = 0;
    std::vector<std::string> files = fileManager::getFiles( dir );

    for( auto it : files ){
      try{
        load( dir + it );
        ++count;
      }catch( std::exception& ){
        //If it fails, don't count it, move along
      }
    }

    return count;
  }

  pointer createObject( const std::string& name ){
    const registerParams* rp = mObjMap.at( name );
    create_t cr = ( create_t )rp->create;

    return ( pointer )cr();
  }

  int registerObject( const std::string& name, const registerParams* rp ){
    if( mServices.version.minor != rp->version.minor ){
      throw incompatibleVersionException( rp->version, mServices.version );
    }

    mObjMap[name] = rp;
    //mObjMap.insert( std::pair<std::string, const registerParams*>( std::string( ( const char* )name ), rp ) );

    return 0;
  }

  std::vector<std::string> getNames(){
    std::vector<std::string> names;
    for( auto it : mObjMap ){
      names.push_back( it.first );
    }
    return names;
  }
};

#endif

