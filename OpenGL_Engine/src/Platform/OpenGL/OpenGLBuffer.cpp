#include "gbpch.h"
#include "OpenGLBuffer.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
namespace GB
{
#pragma region Vertex Buffer
  
  OpenGLVertexBuffer * OpenGLVertexBuffer::Create(float * vertices, unsigned int * indices)
  {
    glCreateBuffers(1, &m_RenderID);
    return nullptr;
  }

  void OpenGLVertexBuffer::Bind() const
  {
  }
  void OpenGLVertexBuffer::UnBind() const
  {
  }

#pragma endregion

#pragma region IndexBuffer

  void OpenGLIndexBuffer::Bind() const
  {
  }
  void OpenGLIndexBuffer::UnBind() const
  {
  }
  OpenGLIndexBuffer * OpenGLIndexBuffer::Create(float * vertices, unsigned int * indices)
  {
    return nullptr;
  }
#pragma endregion

}