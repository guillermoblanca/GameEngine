#include "gbpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"
namespace GB
{
  static GLenum ShaderDataTypeToOpenGLBaseType(EShaderDataType type)
  {
    switch (type)
    {
    case GB::EShaderDataType::None:   return 0;
    case GB::EShaderDataType::Mat3:   return GL_FLOAT_MAT3;
    case GB::EShaderDataType::Mat4:   return GL_FLOAT_MAT4;
    case GB::EShaderDataType::Float:  return GL_FLOAT;
    case GB::EShaderDataType::Float2: return GL_FLOAT;
    case GB::EShaderDataType::Float3: return GL_FLOAT;
    case GB::EShaderDataType::Float4: return GL_FLOAT;
    case GB::EShaderDataType::Int:    return GL_INT;
    case GB::EShaderDataType::Int2:   return GL_INT;
    case GB::EShaderDataType::Int3:   return GL_INT;
    case GB::EShaderDataType::Int4:   return GL_INT;
    case GB::EShaderDataType::Bool:   return GL_BOOL;
    }
    //error
    return 0;
  };


  OpenGLVertexArray::OpenGLVertexArray()
  {
    glCreateVertexArrays(1, &m_RenderID);

  }
  OpenGLVertexArray::~OpenGLVertexArray()
  {
    glDeleteVertexArrays(1, &m_RenderID);
  }
  void OpenGLVertexArray::Bind() const
  {
    glBindVertexArray(m_RenderID);
  }
  void OpenGLVertexArray::UnBind() const
  {
    glBindVertexArray(0);
  }
  void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer)
  {
    GB_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has no layout!");
    
    glBindVertexArray(m_RenderID);
    vertexBuffer->Bind();

    uint32_t index = 0;
    auto& layout = vertexBuffer->GetLayout();
    for (const auto& element : layout)
    {
      glEnableVertexAttribArray(index);
      glVertexAttribPointer(index,
        element.GetComponentCount(),
        ShaderDataTypeToOpenGLBaseType(element.Type),
        element.Normalized ? GL_TRUE : GL_FALSE,
        layout.GetStride(),
        (const void*)element.Offset);
      index++;
    }
    m_vertexBuffers.push_back(vertexBuffer);
  }
  void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer)
  {
    glBindVertexArray(m_RenderID);
    indexBuffer->Bind();
    m_indexBuffer = indexBuffer;
  }
}