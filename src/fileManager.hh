#ifndef __FILE_MANAGER_H__
#define __FILE_MANAGER_H__

class fileManager{
public:
  static std::vector<std::string> getFiles(const std::string& dir);
};

#endif

