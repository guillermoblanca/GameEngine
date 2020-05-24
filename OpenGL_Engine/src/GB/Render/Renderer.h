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
  class GBAPI Renderer
  {
  public:
    Renderer();
    ~Renderer();

    //Get the Current API in use
    inline static RendererAPI::API GetAPI() { return RendererAPI::API::OpenGL; }

    void Init();
    void ShutDown();

    void OnRender();
    void OnImguiRender();

    static void BeginScene(Camera camera);
    static void EndScene();
    static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

    void AddRenderElement(const RenderObject& renderElement);
    void AddRenderElement(RenderObject&& renderElement);

    inline RenderObject* GetRenderobj(unsigned int index) { if (index > m_renderObjects.size() - 1)return nullptr; else return &m_renderObjects[index]; }
    size_t  GetRenderObjectCount() { return m_renderObjects.size(); }


	inline const std::vector<Material*> GetMaterials() { return m_materials; }

    //change this to new style
    std::vector<Texture2D*> m_textures;
    std::vector<Material*> m_materials;

  private:

	void RenderObjectImgui(GB::RenderObject*& render, int i, glm::vec3& scale, glm::quat& quat, glm::vec3& position, glm::vec3& skew, glm::vec4& perspective, float  rot[3]);
    glm::vec4 renderColor;

    uint32_t m_VertexArray;

    std::vector<RenderObject> m_renderObjects;
  };



}
