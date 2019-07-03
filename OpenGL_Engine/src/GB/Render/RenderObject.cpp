#include "gbpch.h"
#include "RenderObject.h"
#include "Buffer.h"
#include "Math.h"
#include "Camera.h"
#include "glad/glad.h"
/*
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
*/
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

  RenderObject::RenderObject(std::string name) :m_name(name), m_indexbuffer(), m_transform(), m_color(1.0f)
  {
  }
  RenderObject::~RenderObject()
  {

  }
  void RenderObject::UnBind()
  {
    m_indexbuffer->UnBind();
  }


  void RenderObject::Create(float* vertices, uint32_t size, uint32_t* indices, uint32_t count)
  {
    m_vertexBuffer.reset(VertexBuffer::Create(vertices, size));

    BufferLayout layout = {
      { EShaderDataType::Float3,"_Position"},
      { EShaderDataType::Float2,"_TexCoord"}
    };

    uint32_t index = 0;
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

    m_vertexBuffer->SetLayout(layout);
    m_indexbuffer.reset(IndexBuffer::Create(indices, count));

  }
  void RenderObject::Render(Material& material, int mode)
  {
    m_vertexBuffer->Bind();
    m_indexbuffer->Bind();

    material.Bind();
    material.SetMat4("u_transform", m_transform.GetMat4());
    material.SetMat4("u_view", Camera::GetView());
    material.SetMat4("u_proj", Camera::GetProj());
    material.SetVector4("u_Color", m_color.r, m_color.g, m_color.b, m_color.a);
    material.SetInt("u_Texture", 0);

    glDrawElements(mode, m_indexbuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
  }

  Sprite::Sprite(uint32_t textID)
  {
    this->m_textureID = textID;
    float verticesPlane[]
    {//vertices           //uv
      -0.5f, -0.5f,0.0f, 0.0f, 0.0f,
       0.5f, -0.5f,0.0f, 1.0f, 0.0f,
       0.5f, 0.5f,0.0f,  1.0f, 1.0f,
      -0.5f, 0.5f,0.0f,  0.0f, 1.0f
    };

    uint32_t indicesPlane[]
    {
      0,1,2,
      2,3,0
    };
    this->Create(verticesPlane, sizeof(verticesPlane), indicesPlane, sizeof(indicesPlane) / sizeof(uint32_t));
  }
  Sprite::~Sprite()
  {

  }
}