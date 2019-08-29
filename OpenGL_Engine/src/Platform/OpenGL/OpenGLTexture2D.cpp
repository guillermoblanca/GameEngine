#include "gbpch.h"
#include "OpenGLTexture2D.h"
#include "glad\glad.h"
#include "Platform\stb\stb_image.h"

namespace GB
{

  OpenGL_Texture2D::OpenGL_Texture2D(const std::string path)
  {
    stbi_set_flip_vertically_on_load(true);
    auto m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);

    //  GB_CORE_ERROR("FAIL Reason {0}, path: {1}", stbi_failure_reason(),path.c_str());
    glGenTextures(1, &m_ID);

    glBindTexture(GL_TEXTURE_2D, m_ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    if (m_LocalBuffer)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
      GB_CORE_ERROR("Texture error when loading");
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_LocalBuffer) stbi_image_free(m_LocalBuffer);

  }

  OpenGL_Texture2D::~OpenGL_Texture2D()
  {
    glDeleteTextures(1, &m_ID);
  }

  void OpenGL_Texture2D::Bind(uint32_t slot) const
  {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_ID);
  }

  void OpenGL_Texture2D::UnBind() const
  {
  }


}
