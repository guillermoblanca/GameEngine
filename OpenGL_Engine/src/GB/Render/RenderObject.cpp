#include "gbpch.h"
#include "RenderObject.h"
#include "Buffer.h"
#include "Math.h"
#include "Camera.h"
#include "glad/glad.h"

namespace GB
{

  RenderObject::RenderObject(std::string name) :m_name(name), m_transform(), m_color(1.0f)
  {
  }
  RenderObject::~RenderObject()
  {

  }
  void RenderObject::UnBind()
  {
    m_vertexArray->UnBind();
  }

  void RenderObject::Create(float* vertices, uint32_t size, uint32_t* indices, uint32_t count)
  {
    m_vertexArray.reset(VertexArray::Create());

    std::shared_ptr<VertexBuffer> vertexBuffer;
    vertexBuffer.reset(VertexBuffer::Create(vertices, size));

    BufferLayout layout = {
      { EShaderDataType::Float3,"_Position"},
      { EShaderDataType::Float2,"_TexCoord"}
    };

    vertexBuffer->SetLayout(layout);
    m_vertexArray->AddVertexBuffer(vertexBuffer);

    std::shared_ptr<IndexBuffer> indexBuffer;
    indexBuffer.reset(IndexBuffer::Create(indices, count));
    m_vertexArray->SetIndexBuffer(indexBuffer);
  }
  void RenderObject::Render(Material& material, int mode)
  {
    material.Bind();
    material.SetMat4("u_transform", m_transform.GetMat4());
    material.SetMat4("u_view", Camera::GetView());
    material.SetMat4("u_proj", Camera::GetProj());
    material.SetVector4("u_Color", m_color.r, m_color.g, m_color.b, m_color.a);
    material.SetInt("u_Texture", 0);

    m_vertexArray->Bind();
    glDrawElements(mode, m_vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
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