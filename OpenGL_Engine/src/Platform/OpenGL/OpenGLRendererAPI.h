#pragma once

#include "GB/Render/RendererAPI.h"
#include "GB/Math.h"
namespace GB
{
  class OpenGLRendererAPI : public RendererAPI
  {
  public:
    virtual void SetClearColor(const glm::vec4& color) override;
    virtual void Clear() override;
    virtual void AlphaMode(bool active) override;
    virtual void DephtTest(bool active) override;
    virtual void LightMode(bool active) override;

    virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
  };
}