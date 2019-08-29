#pragma once

#include "RendererAPI.h"
namespace GB
{
  class RenderCommand
  { 
  public:


    inline static void DrawIndex(const std::shared_ptr<VertexArray>& vertexArray)
    {
      s_RendererAPI->DrawIndexed(vertexArray);
    }
    inline static void Clear()
    {
      s_RendererAPI->Clear();
    }
    inline static void SetClearColor(const glm::vec4 & color)
    {
      s_RendererAPI->SetClearColor(color);
    }
    inline static void AlphaMode(bool active)
    {
      s_RendererAPI->AlphaMode(active);
    }
    inline static void DephtTest(bool active)
    {
      s_RendererAPI->DephtTest(active);
    }
  private:
    static RendererAPI* s_RendererAPI;
  };
}