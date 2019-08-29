#pragma once
#include "GB/Render/Texture2D.h"
namespace GB
{

  class  OpenGL_Texture2D : public Texture2D
  {
  public:
    OpenGL_Texture2D(const std::string path);
    ~OpenGL_Texture2D();

    virtual void Bind(uint32_t slot)const override;
    virtual void UnBind()const override;

  };
}