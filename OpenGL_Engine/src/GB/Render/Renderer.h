#pragma once

#include "gbpch.h"

#include "GB/Core.h"
#include "GB\Layer.h"
#include "Material.h"
#include "RenderObject.h"

namespace GB
{
  enum class ERendererAPI
  {
    None = 0, OpenGL = 1
  };

  //todo: refactor class to singleton instance 
  class GBAPI Renderer : public Layer
  {
  public:


    enum class ERenderMode {
      Lines = 0x0001,
      LinesLoop = 0x0002,
      Triangles = 0x0004
    };
    Renderer();
    ~Renderer();
    inline static Renderer& Get() { return *m_singleton; }
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnRender();
    virtual void OnImguiRender() override;

    virtual void Begin();
    virtual void End();//todo: not working

    void PushObj(RenderObject* obj);
    void PushOverLay(RenderObject* obj);
    void PopObj(RenderObject* obj);
    void PopOverlay(RenderObject* obj);

    inline RenderObject* GetRenderobj(unsigned int index) { return m_renderObjects[index];  }
    uint32_t  GetRenderObjectCount() { return (uint32_t)m_renderObjects.size(); }
    void SetRenderMode(ERenderMode mode);

    glm::vec4 renderColor;

    inline static ERendererAPI GetAPI() { return m_rendererAPI; }
  private:
    uint32_t m_VertexArray;
    static Renderer *m_singleton;
    static ERendererAPI m_rendererAPI;
    std::vector<RenderObject*> m_renderObjects;
    std::vector<Material*> m_materials;
    std::vector<Texture*> m_textures;

    ERenderMode mode;
    unsigned int m_renderIndex;

    void AlphaRender(bool active);

  };



}
