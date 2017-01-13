#ifndef __FILE_MANAGER_H__
#define __FILE_MANAGER_H__

#include<string>

//TODO: update to use c++ 17 file system API
class fileManager{
public:
  static std::vector<std::string> getFiles( const std::string& dir );
};

#endif

