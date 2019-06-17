#include "gbpch.h"
#include "OpenGLBuffer.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
namespace GB
{
#pragma region VertexBuffer


  OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) 
  {
    //GB_CORE_ASSERT(glGetError() == 0, "Create error: {0}", glGetError());

    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    //GB_CORE_ASSERT(glGetError() == 0, "Create error: {0}", glGetError());

  }

  OpenGLVertexBuffer::~OpenGLVertexBuffer()
  {
    glDeleteBuffers(1, &m_RendererID);
  }

  void OpenGLVertexBuffer::Bind() const
  {
    
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
  }
  void OpenGLVertexBuffer::UnBind() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

#pragma endregion

#pragma region IndexBuffer

  OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
  {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t),indices, GL_STATIC_DRAW);
    
  }

  void OpenGLIndexBuffer::Bind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
  }
  void OpenGLIndexBuffer::UnBind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

#pragma endregion

}