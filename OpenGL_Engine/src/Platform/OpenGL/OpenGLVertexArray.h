#pragma once
#include "GB/Render/VertexArray.h"
namespace GB
{
  class OpenGLVertexArray :public VertexArray
  {
  public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void Bind()   const override;
    virtual void UnBind() const override;
    virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer) override;
    virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer) override;
    virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers()const override { return m_vertexBuffers; }
    virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer()const override { return m_indexBuffer; }
  private:
    std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
    uint32_t m_RenderID;
  };
}