#pragma once

#include "gbpch.h"

#include "RendererAPI.h"
#include "GB/Core.h"
#include "GB/Layer.h"
#include "Material.h"
#include "RenderObject.h"
#include "Camera.h"

//todo: remove this in the future
#include "GB/Render/Texture2D.h"
namespace GB
{
  class GBAPI Renderer : public Layer
  {
  public:
    //Get the Current API in use
    inline static RendererAPI::API GetAPI() { return RendererAPI::API::OpenGL; }

    /*
    This will update lights and cameras
    */
    static void BeginScene(Camera camera);
    static void EndScene();

    static void Submit(const std::shared_ptr<VertexArray>& vertexArray);


    ////////////////////////////////////////////////
    ////////////////////// OLD STUFF ///////////////
    ////////////////////////////////////////////////
    enum class ERenderMode {
      Lines     = 0x0001,
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

    void PushObj(RenderObject* obj);
    void PushOverLay(RenderObject* obj);
    void PopObj(RenderObject* obj);
    void PopOverlay(RenderObject* obj);

    inline RenderObject* GetRenderobj(unsigned int index) { if (index > m_renderObjects.size() - 1)return nullptr; else return m_renderObjects[index]; }
    int  GetRenderObjectCount() { return m_renderObjects.size(); }
	inline const std::vector<Material*> GetMaterials() { return m_materials; }
    void SetRenderMode(ERenderMode mode);

    glm::vec4 renderColor;


  private:
    uint32_t m_VertexArray;
    static Renderer *m_singleton;
    std::vector<RenderObject*> m_renderObjects;
    std::vector<Material*> m_materials;
    std::vector<Texture2D*> m_textures;

    ERenderMode mode;
    unsigned int m_renderIndex;
  };



}
