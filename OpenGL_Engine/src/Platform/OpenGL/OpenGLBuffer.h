#pragma once
#include "gbpch.h"
#include "GB/Render/Buffer.h"

namespace GB
{
  class OpenGLVertexBuffer : public VertexBuffer
  {
  public:
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    virtual ~OpenGLVertexBuffer();

    virtual void Bind() const override;
    virtual void UnBind() const override;

    static OpenGLVertexBuffer* Create(float* vertices, unsigned int* indices);

  private:
    static uint32_t m_RenderID;
  };

  class OpenGLIndexBuffer : public IndexBuffer
  {
  public:
    virtual ~OpenGLIndexBuffer() {}

    virtual void Bind()const;
    virtual void UnBind() const;

    static OpenGLIndexBuffer* Create(float* vertices, unsigned int* indices);
  };
}