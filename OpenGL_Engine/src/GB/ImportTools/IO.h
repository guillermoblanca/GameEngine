#pragma once
#include "GB/Core.h"
#include "gbpch.h"
namespace GB
{
  //made flags
  enum class EFileMode
  {
    Text,
    Binary
  };

  template<class T>
  class File
  {
  public:
    uint32_t ID;//identifier for type object
    std::string Path; //Path of file
    std::string Name; //object name
    T data;//data content
  };

  class IO
  {
  public:
    template<class T> static T ReadFile(std::string path);
    template<class T> static bool WriteFile(T data, std::string path);
   
    //int ReadFile(std::string path);
  private:
    //static std::fstream m_stream;
  };
  template<class T>
  inline T IO::ReadFile(std::string path)
  {
    std::ifstream ifile;
    ifile.open(path.c_str(), std::ios::binary | std::ios::in);
    T* data = new T();
    //ifile.seekg(0);
    ifile.read((char*)data, sizeof(T));
    ifile.close();
    return *data;
  }
  template<class T>
  inline bool IO::WriteFile(T data, std::string path)
  {
    std::ofstream ofile(path.c_str(), std::ios::binary | std::ios::out);
    ofile.write((char*)&data, sizeof(T));
    ofile.close();
    return true;
  }
}