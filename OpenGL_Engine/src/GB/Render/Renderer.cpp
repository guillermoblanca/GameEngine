#include "gbpch.h"
#include "Renderer.h"
#include "imgui.h"
#include "Buffer.h"

#include "GB/Application.h"
#include "GB/Math.h"
#include "GB/Input.h"
#include "GB/Render/RenderCommand.h"


namespace GB
{
  Renderer* Renderer::m_singleton = nullptr;


  void Renderer::BeginScene(Camera camera)
  {
  }

  void Renderer::EndScene()
  {
  }

  void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
  {
    vertexArray->Bind();
    RenderCommand::DrawIndex(vertexArray);
  }

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


    RenderCommand::AlphaMode(true);
    RenderCommand::DephtTest(true);
    std::vector<std::string> paths;
    paths.push_back("Assets/Texture/ball.png");
    paths.push_back("Assets/Texture/Brick.png");
    paths.push_back("Assets/Texture/Game.png");
    paths.push_back("Assets/Texture/lion-logo.png");

    for (int i = 0; i < paths.size(); i++)
    {
      m_textures.push_back(Texture2D::Create(paths[i]));
      m_textures[i]->Create(paths[i]);
    }

    PushObj(new Sprite(3,"Plane 0"));
    PushObj(new Sprite(0,"Plane 1"));
    PushObj(new Cube(1,"Cube"));
    PushObj(new Cube(0,"Cube white"));
    PushObj(new Line(vector2(0.0f, 0.0f), vector2(2.0f, 2.0f)));
    m_materials.push_back(new Material("Assets/Shader/Camera.shader"));


    {
      /*
      For setting random position
      */
      int distance = 4;
      for (int i = 0; i < m_renderObjects.size(); i++)
      {
        vector3 randomPos = vector3(Mathf::Random(-distance, distance), Mathf::Random(-distance, distance), 0.0f);

        auto render = m_renderObjects[i];
        render->m_transform.position = randomPos;
      }
    }

  }
  void Renderer::OnDetach()
  {
    for (int i = 0; i < m_textures.size(); i++) delete m_textures[i];
    for (int i = 0; i < m_renderObjects.size(); i++) delete m_renderObjects[i];
  }

  void Renderer::OnRender()
  {

    //Loop for renderOjects and setting different options
    for (int i = 0; i < m_renderObjects.size(); i++)
    {
      RenderObject* obj = m_renderObjects[i];
      m_textures[obj->m_textureID]->Bind(0);
      obj->Render(*m_materials[0], (int)mode);
    }

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
    if (ImGui::Button("Get random number")) { random = Mathf::Random(10, 100); }
    if (ImGui::Button("Change Alpha mode")) { useAlpha = !useAlpha; RenderCommand::AlphaMode(useAlpha); }
    ImGui::Text("Random number generator: %d", random);
    if (ImGui::CollapsingHeader("Background Color"))
    {
      ImGui::ColorPicker4("Render Color", (float*)&renderColor);
    }
    if (ImGui::CollapsingHeader("All textures"))
    {
      for (int i = 0; i < m_textures.size(); i++)
        ImGui::Image((ImTextureID)m_textures[i]->GetID(), ImVec2(200, 200));

    }

    if (ImGui::Button("Add Plane"))
    {
      PushObj(new Sprite(Mathf::Random(0, m_textures.size() - 1)));
    }
    ImGui::SameLine();
    if (ImGui::Button("Add Cube"))
    {
      PushObj(new Cube(Mathf::Random(0, m_textures.size() - 1)));
    }
    if (ImGui::Button("Remove Last RenderObject") && !m_renderObjects.empty())
    {
      int index = m_renderObjects.size() - 1;
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
          ImGui::InputText("Name:", render->m_name.data(), 64);
          ImGui::DragFloat3("Position", (float*)&position, 0.1f);
          ImGui::DragFloat3("Rotation", rot, 0.1f);
          ImGui::DragFloat3("Scale", (float*)&scale, 0.1f);

          ImGui::Separator();
          ImGui::Text("Pos: %2f,%2f,%2f", position.x, position.y, position.z);
          ImGui::Text("Rotation: %2f,%2f,%2f", Mathf::ToDegrees(rotator.x), Mathf::ToDegrees(rotator.y), Mathf::ToDegrees(rotator.z));
          ImGui::Text("Scale: %2f,%2f,%2f", scale.x, scale.y, scale.z);
          ImGui::Separator();

          if (ImGui::CollapsingHeader("Color properties", ImGuiTreeNodeFlags_Bullet))
          {
            ImGui::DragInt("Texture", &m_renderObjects[i]->m_textureID, 1, 0, m_textures.size() - 1);
            if (ImGui::Button("Texture Up")) m_renderObjects[i]->m_textureID = Mathf::Clamp<int>(m_renderObjects[i]->m_textureID + 1, 0, m_textures.size() - 1);
            ImGui::SameLine();
            if (ImGui::Button("Texture Down")) m_renderObjects[i]->m_textureID = Mathf::Clamp<int>(m_renderObjects[i]->m_textureID - 1, 0, m_textures.size() - 1);
            ImGui::ColorPicker4("Color", (float*)&render->m_color);
            ImGui::Image((ImTextureID)m_textures[render->m_textureID]->GetID(), ImVec2(200, 200));
          }
		  
		  if (render->mesh != nullptr) render->mesh->WindowProperties();

          render->m_transform.Translate(position);
          render->m_transform.Rotate(glm::vec3(glm::radians(rot[0]), glm::radians(rot[1]), glm::radians(rot[2])));
		  render->m_transform.SetScale(scale);
          ImGui::TreePop();
        }
      ImGui::TreePop();
    }
    ImGui::End();


  }
}