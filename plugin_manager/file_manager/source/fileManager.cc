#include<iostream>
#include<vector>
#include<dirent.h>

#include"../include/fileManager.hh"

directoryExistenceException::directoryExistenceException( const std::string& dir ):
  mMesg( "Error opening " + dir + "." ){
}

const char* directoryExistenceException::what() const noexcept{
  return mMesg.c_str();
}

std::vector<std::string> fileManager::getFiles( const std::string& dir ){
  DIR *dp;
  struct dirent *dirp;
  std::string bad1( "." );
  std::string bad2( ".." );
  std::vector<std::string> files;

  if( ( dp = opendir( dir.c_str() ) ) == NULL ) {
    throw directoryExistenceException( dir );
  }

  while ( ( dirp = readdir( dp ) ) != NULL ) {
    std::string tmp( dirp->d_name );
    if( tmp != bad1 && tmp!= bad2 ){
      files.push_back( tmp );
    }
  }

  closedir( dp );
  return files;
}

