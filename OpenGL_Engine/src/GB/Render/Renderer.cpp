#include "gbpch.h"
#include "Renderer.h"


#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Buffer.h"

#include "GB/Application.h"
#include "imgui.h"
#include "GB/Math.h"
#include "GB/Input.h"
#include "Camera.h"

namespace GB
{
  Renderer* Renderer::m_singleton = nullptr;
  ERendererAPI Renderer::m_rendererAPI = ERendererAPI::OpenGL;


  Renderer::Renderer() : m_renderIndex(0), renderColor(0, 0.5f, 0.5f, 1.0f)
  {
    m_singleton = this;
  }

  Renderer::~Renderer()
  {
    for (RenderObject* render : m_renderObjects)
    {
      delete render;
    }

    for (Material* mat : m_materials)
    {
      delete mat;
    }
  }

  void Renderer::OnAttach()
  {
    GB_CORE_INFO("Initialized Render class");

    float verticesCube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,//0
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,//1
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,//2
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,//3

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,//4
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,//5
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,//6
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,//7

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,//8
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,//9
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,//10

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,//11
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,//12
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,//13

     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,//14
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,//15
    };

    uint32_t indiceCube[]
    {
    0,1,2,2,3,0,
    4,5,6,6,7,4,
    8,9,10,10,4,8,
    11,2,12,12,13,11,
    10,14,5,5,4,10,
    3,2,11,11,15,3
    };
    float verticesPlane[]
    {//vertices           //uv
      -0.5f,-0.5f,0.0f, 0.0f, 0.0f,
       0.5f,-0.5f,0.0f,  1.0f, 0.0f,
       0.5f, 0.5f,0.0f, 1.0f, 1.0f,
      -0.5f, 0.5f,0.0f, 0.0f, 1.0f
    };

    uint32_t indicesPlane[]
    {
      0,1,2,
      2,3,0
    };

    AlphaRender(true);
    glEnable(GL_DEPTH_TEST);

    m_textures.push_back(new Texture("Assets/Texture/ball.png", 0));
    m_textures.push_back(new Texture("Assets/Texture/Brick.png", 1));
    m_textures.push_back(new Texture("Assets/Texture/Game.png", 1));

    PushObj(new RenderObject("Plane 0"));
    RenderObject* render = (RenderObject*)m_renderObjects[0];
    render->Create(verticesPlane, sizeof(verticesPlane), indicesPlane, sizeof(indicesPlane) / sizeof(uint32_t));
    render->m_textureID = 0;

    PushObj(new RenderObject("Plane 1"));
    render = (RenderObject*)m_renderObjects[1];
    render->Create(verticesPlane, 5 * 4 * sizeof(float), indicesPlane, 6);
    render->m_textureID = 0;

    PushObj(new RenderObject("Cube"));
    render = (RenderObject*)m_renderObjects[2];
    render->Create(verticesCube, 5 * 16 * sizeof(float), indiceCube, 36);
    render->m_textureID = 1;

    PushObj(new RenderObject("Cube white"));
    render = m_renderObjects[3];
    render->Create(verticesCube, 5 * 16 * sizeof(float), indiceCube, 36);
    render->m_textureID = 0;

    m_materials.push_back(new Material("Assets/Shader/Camera.shader"));
  }
  void Renderer::OnDetach()
  {
    for (int i = 0; i < m_textures.size(); i++) delete m_textures[i];
    for (int i = 0; i < m_renderObjects.size(); i++) delete m_renderObjects[i];
  }

  void Renderer::OnRender()
  {
    Begin();
    for (int i = 0; i < m_renderObjects.size(); i++)
    {
      RenderObject* obj = m_renderObjects[i];
      m_textures[obj->m_textureID]->Bind();
      obj->Render(*m_materials[0], (int)mode);
    }
  }


  void Renderer::Begin()
  {
    glClearColor(renderColor.r, renderColor.g, renderColor.b, renderColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void Renderer::End()
  {
    static auto window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
    glfwSwapBuffers(window);
  }
  void Renderer::PushObj(RenderObject * obj)
  {
    m_renderObjects.emplace(m_renderObjects.begin() + m_renderIndex, obj);
    m_renderIndex++;
  }
  void Renderer::PushOverLay(RenderObject * obj)
  {
    m_renderObjects.emplace_back(obj);
  }
  void Renderer::PopObj(RenderObject * obj)
  {
    auto it = std::find(m_renderObjects.begin(), m_renderObjects.end(), obj);
    if (it != m_renderObjects.end())
    {
      m_renderObjects.erase(it);
      m_renderIndex--;
    }
  }
  void Renderer::PopOverlay(RenderObject * obj)
  {
    auto it = std::find(m_renderObjects.begin(), m_renderObjects.end(), obj);
    if (it != m_renderObjects.end())
      m_renderObjects.erase(it);
  }
  void Renderer::SetRenderMode(ERenderMode mode)
  {
    this->mode = mode;
  }
  void Renderer::OnImguiRender()
  {
    static int random = 0;
    static bool useAlpha = true;
    static int i = 0;
    static float rot[] = { 0,0,0 };
    glm::vec3 position;
    glm::quat quat;
    glm::vec3 scale;
    glm::vec3 skew;
    glm::vec4 perspective;
    RenderObject* render = nullptr;

    ImGui::Begin("Render");
    if (ImGui::Button("Get random number")) { random = Math::Random(10, 100); }
    if (ImGui::Button("Change Alpha mode")) { useAlpha = !useAlpha; this->AlphaRender(useAlpha); }
    ImGui::Text("Random number generator: %d", random);
    if (ImGui::CollapsingHeader("Background Color"))
    {
      ImGui::ColorPicker4("Render Color", (float*)&renderColor);
    }
    if (ImGui::Button("Add RenderObject"))
    {
     //todo: fix issue render deformation
      PushObj(new Sprite(2));
    }
    if (ImGui::Button("Remove Last RenderObject"))
    {
      uint32_t index = m_renderObjects.size() - 1; 
      PopObj(m_renderObjects[index]);
    }
    
    ImGui::DragInt("INDEX", &i, 1, 0, (int)m_renderObjects.size() - 1); ImGui::SameLine();
    ImGui::Text("%d", m_renderObjects.size());
    if (ImGui::TreeNode("RenderObject Info"))
    {
      for (int i = 0; i < m_renderObjects.size(); i++)
        if (ImGui::TreeNode((void*)(intptr_t)i, "%s", m_renderObjects[i]->m_name.c_str()))
        {
          render = m_renderObjects[i];
          glm::decompose(render->m_transform.GetMat4(), scale, quat, position, skew, perspective);
          glm::vec3 rotator = render->m_transform.rotation;

          ImGui::DragFloat3("Position", (float*)&position, 0.1f);
          ImGui::DragFloat3("Rotation", rot, 0.1f);
          ImGui::Separator();
          ImGui::Text("Pos: %2f,%2f,%2f", position.x, position.y, position.z);
          ImGui::Text("Rotation: %2f,%2f,%2f", Math::ToDegrees(rotator.x), Math::ToDegrees(rotator.y), Math::ToDegrees(rotator.z));
          ImGui::Text("Scale: %2f,%2f,%2f", scale.x, scale.y, scale.z);
          ImGui::Separator();

          if (ImGui::CollapsingHeader("Color properties", ImGuiTreeNodeFlags_Bullet))
          {
            ImGui::ColorPicker4("Color", (float*)&render->m_color);
            ImGui::Image((ImTextureID)m_textures[render->m_textureID]->GetID(), ImVec2(200, 200));
          }


          render->m_transform.Translate(position);
          render->m_transform.Rotate(glm::vec3(glm::radians(rot[0]), glm::radians(rot[1]), glm::radians(rot[2])));
          ImGui::TreePop();
        }
      ImGui::TreePop();
    }
    ImGui::End();


  }
  void Renderer::AlphaRender(bool active)
  {
    if (active)
    {

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else
    {
      glDisable(GL_BLEND);
    }
  }
}