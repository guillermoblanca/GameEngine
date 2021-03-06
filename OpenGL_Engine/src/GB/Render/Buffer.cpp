#include "gbpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
namespace GB
{

   VertexBuffer * VertexBuffer::Create(float * vertices, uint32_t size)
   {
     switch (Renderer::GetAPI())
     {
     case RendererAPI::API::None: GB_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
     case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
     }
     GB_CORE_ASSERT(false, "Unknow RendererAPI");

     return nullptr;
   }
   IndexBuffer * IndexBuffer::Create(uint32_t * indices, uint32_t count)
   {
     switch (Renderer::GetAPI())
     {
     case RendererAPI::API::None: GB_CORE_ASSERT(false, "RendererAPI::None is not supported");
     case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, count);
     }
     
     GB_CORE_ASSERT(false, "Unknow RendererAPI");
     return nullptr;
   }
}