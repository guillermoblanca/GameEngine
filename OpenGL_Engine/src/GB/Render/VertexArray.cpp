#include "gbpch.h"
#include "VertexArray.h"
#include "GB/Render/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace GB
{
  VertexArray* VertexArray::Create()
  {
    switch (Renderer::GetAPI())
    {
    case ERendererAPI::None: GB_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
    case ERendererAPI::OpenGL: return new OpenGLVertexArray();
    }
    GB_CORE_ASSERT(false, "Unknow RendererAPI");

    return nullptr;
  }
}