#pragma once
#include "gbpch.h"
#include "GB\Core.h"
namespace GB
{


  class Texture2D
  {
  public:

    /*Function to create the texture2D*/
    static Texture2D* Create(const std::string path);

    /*Bind the texture to current shader*/
    virtual void Bind(uint32_t slot)const = 0;
    /*Unbind the texture to the current shader*/
    virtual void UnBind()const = 0;

    inline int32_t GetID() { return m_ID; }
    inline int GetBPP() { return m_BPP; }
    inline int GetWidth() { return m_Width; }
    inline int GetHeight() { return m_Height; }
  protected:
    unsigned int m_ID = -1;
    int m_BPP = 0;
    int m_Width;
    int m_Height;

  };
}
