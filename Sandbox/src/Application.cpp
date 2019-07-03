#include "GB.h"
#include "Application.h"
#include "imgui\imgui.h"

using namespace GB;

struct DATA
{
  vector2 position;
  unsigned int ID;
  std::string name;
};
void LayerExample::OnImguiRender()
{

  ImGui::Begin("Console");
  ImGui::Text("Hello world!");
  bool state = ImGui::Button("Clear console");
  if (state)
  {
    GB_CLIENT_INFO("Button pushed!");
  }
  ImGui::End();
}

void LayerExample::OnEvent(GB::Event & event)
{


  if (event.GetEventType() == GB::EventType::KeyPressed)
  {
    GB::MouseScrolledEvent& e = (GB::MouseScrolledEvent&) event;
  }
}


#pragma region FreeCamera


vector2 FreeCamera::CameraDirection()
{
  mouse = GB::Input::GetMousePosition();
  vector2 diff = mouse - prevMouse;

  prevMouse = mouse;
  return diff;
}



void FreeCamera::OnAttach()
{
  Camera::Translate(glm::vec3(0.0f, 0.0f, -10.0f));
}

float velocity = 5.0f;
void FreeCamera::OnUpdate()
{

  unsigned int id = 1;


  RenderObject* obj = (RenderObject*)Renderer::Get().GetRenderobj(id);
  if (obj == nullptr)return;
  static unsigned int count = Renderer::Get().GetRenderObjectCount();

  for (int i = 1; i < count; i++)
  {
    RenderObject* render = (RenderObject*)Renderer::Get().GetRenderobj(i);
    vector2 position = vector2(render->m_transform.position.x, render->m_transform.position.y);
    BoxCollider box = { position,1,1 };

    RenderObject* render1 = (RenderObject*)Renderer::Get().GetRenderobj(i - 1);
    vector2 position1 = vector2(render1->m_transform.position.x, render1->m_transform.position.y);
    BoxCollider box1 = { position1,1,1 };

    if (CollisionManager::CheckCollision(box1, box))
    {
      render->m_color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

      //GB_CORE_INFO("Obj {0}, Obj2 {1}", render->m_transform.position, render1->m_transform.position);
    }
    else
    {
      render->m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    }
  }

  if (Input::IsKeyPressed(GB_KEY_W))
  {
    obj->m_transform.position = obj->m_transform.position + (glm::vec3(0.f, velocity * Time::DeltaTime(), 0.0f));
  }
  else
    if (Input::IsKeyPressed(GB_KEY_D))
    {
      obj->m_transform.position = obj->m_transform.position + (glm::vec3(velocity * Time::DeltaTime(), 0.0f, 0.0f));
    }
  if (Input::IsKeyPressed(GB_KEY_A))
  {
    obj->m_transform.position = obj->m_transform.position + (glm::vec3(-velocity * Time::DeltaTime(), 0.0f, 0.0f));
  }
  else if (Input::IsKeyPressed(GB_KEY_S))
  {
    obj->m_transform.position = obj->m_transform.position + (glm::vec3(0.0f, -velocity * Time::DeltaTime(), 0.0f));
  }

  timer += Time::DeltaTime();
  //	obj->m_transform.Lerp0(glm::vec3(0.0f, 0.0f, 0.0f), destiny, std::abs(std::sin(timer)));
  float x = Input::GetMouseX() / (float)Application::Get().GetWindow().GetWidth() * 16;
  float y = Input::GetMouseY() / (float)Application::Get().GetWindow().GetHeight() * 16;
  //obj->m_transform.Translate(glm::vec3((x, y, 0.0f)));
  Camera::CameraInput(velocity);
  if (GB::Input::IsMousePressed(1))
  {

    vector2 diff = CameraDirection();
    GB::Camera::Translate(glm::vec3(diff.x*velocity, -diff.y*velocity, 0.0f));
  }

  if (GB::Input::IsMousePressed(2))
  {
    float diff = CameraDirection().y;
    GB::Camera::Translate(glm::vec3(0.0f, 0.0f, diff *velocity * 2));

  }

  if (Input::IsKeyPressed(GB_KEY_LEFT_ALT) && Input::IsMousePressed(0))
  {
    vector2 position = CameraDirection();


    GB_CORE_INFO("Pivot point {0}", position);
    GB::Camera::Rotate(position.x, glm::vec3(0.f, 1.0f, 0.0f));
    GB::Camera::Rotate(position.y, glm::vec3(1.f, 0.0f, 0.0f));
  }

}

void FreeCamera::OnImguiRender()
{

  static int rendermode = 4;

  RenderObject* obj = (RenderObject*)Renderer::Get().GetRenderobj(1);
  if (obj == nullptr)return;
  GB::Camera::ImguiEditor();
  ImGui::Begin("Profiling");
  ImGui::Text("Time: %2f", timer);
  ImGui::Text("Deltatime: %2f", Time::DeltaTime());
  ImGui::Text("FPS: %f", Time::GetFPS());
  ImGui::SliderFloat("VelocityMove", &velocity, 0.0f, 100.0f);
  ImGui::PlotLines("Time", [](void*data, int idx)
    {
      return idx * Time::DeltaTime();
    }, NULL, 100);

  static bool isvSync = Application::Get().GetWindow().IsVSync();
  if (ImGui::Button("VSync"))
  {
    isvSync = !isvSync;
    Application::Get().GetWindow().SetVSync(isvSync);
  }
  ImGui::SameLine();
  ImGui::Text(isvSync ? "true" : "false");

  ImGui::Text("Mouse %2f,%2f", CameraDirection().x, CameraDirection().y);
  ImGui::DragFloat("Camera distance", &distance);
  ImGui::DragFloat("Velocity", &velocity);
  ImGui::DragFloat3("Destiny", (float*)&destiny);
  if (ImGui::Button("LookAt")) Camera::LookAt(obj->m_transform.position, distance);
  ImGui::DragInt("RenderMode", &rendermode, 1, 0, (int)GB::Renderer::ERenderMode::Triangles);

  Renderer::Get().SetRenderMode(GB::Renderer::ERenderMode(rendermode));

  ImGui::End();

  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Save"))
      {
        DATA data = { vector2(1,2),1,"name" };
        std::ofstream ofile("foo.gb", std::ios::binary | std::ios::out);
        ofile.write((char*)&data, sizeof(DATA));
        ofile.close();
      }
      if (ImGui::MenuItem("Open"))
      {
        /*std::ifstream ifile;
        ifile.open("foo.gb", std::ios::binary | std::ios::in);
        DATA data ;
        ifile.read((char*)&data, sizeof(DATA));
        GB_CORE_INFO("Binary load: {0},{1},{2}", data.position,data.ID,data.name);
        */

        //todo: make work

      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }

}

void FreeCamera::OnEvent(GB::Event & event)
{
  if (event.GetEventType() == GB::EventType::MouseScrolled)
  {

    GB::MouseScrolledEvent& e = (GB::MouseScrolledEvent&) event;
  }

}


#pragma endregion

#pragma region GameSystem

GameSystem* GameSystem::m_instance = new GameSystem();
#pragma endregion

void GameSystem::AddGameObject(GameObject & gameObject)
{
  m_gameObjects.push_back(&gameObject);
}
