#include "gbpch.h"
#include "Texture2D.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture2D.h"
namespace GB
{
  Texture2D* Texture2D::Create(const std::string path)
  {
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::OpenGL:

      return new OpenGL_Texture2D(path);

    case RendererAPI::API::None:
      GB_CORE_ERROR("Not supported use OpenGL instead");
      return nullptr;

    }

      return nullptr;
  }

}