#include "gbpch.h"
#include "Camera.h"
#include "GB\Application.h"
#include "imgui.h"
#include "GB\Input.h"
#include "GB\KeyCodes.h"
namespace GB
{
  Camera::EMode Camera::m_mode = Camera::EMode::Perspective;
  glm::mat4 Camera::m_proj = glm::mat4(1.0f);
  glm::mat4 Camera::m_view = glm::mat4(1.0f);
  glm::vec2 Camera::m_orthoOp = glm::vec2(-1.0f, 1.0f);
  glm::vec3 Camera::m_pos(0.0f, 0.0f, -3.0f);
  glm::vec3 Camera::m_front(0.0f, 0.0f, 0.0f);
  glm::vec3 Camera::m_up(0.0f, 1.0f, 0.0f);
  float Camera::m_fov = 45.0f;
  float Camera::m_nearFOV =0.1f;
  float Camera::m_farFOV = 100.0f;

  Camera::Camera()  
  {
    m_proj = glm::mat4(1.0f);
    m_view = glm::mat4(1.0f);

    m_orthoOp = glm::vec2(-1.0f, 1.0f);
    m_pos =  vector3(0.0f, 0.0f, -3.0f);
    m_front= vector3(0.0f, 0.0f, 0.0f);
    m_up   = vector3(0.0f, 1.0f, 0.0f);

    m_fov = 45.0f;
    m_nearFOV = 0.1f;
    m_farFOV = 100.0f;

    m_mode = EMode::Perspective;
  }


  void Camera::Translate(glm::vec3 pos)
  {
    m_view = glm::translate(m_view, pos);
  }
  void Camera::Rotate(float degrees, vector3 direction)
  {

    m_view = glm::rotate(m_view, glm::radians(degrees), direction);

  }
  void Camera::LookAt(vector3 position, float distance)
  {
    float camX = std::sin(Time::DeltaTime()) * distance;
    float camZ = std::cos(Time::DeltaTime()) * distance;
    m_view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), position, glm::vec3(0.0f, 1.0f, 0.0f));
  }
  void Camera::SetFieldOfView(float degree)
  {
    static float width = (float)Application::Get().GetWindow().GetWidth();
    static float height = (float)Application::Get().GetWindow().GetHeight();
    switch (m_mode)
    {
    case GB::Camera::Perspective:
    {

      m_proj = glm::perspective(glm::radians(m_fov), width / height, m_nearFOV, m_farFOV);
    }
    break;
    case GB::Camera::Orthograpic:
    {
      m_proj = glm::ortho(0.0f, width, 0.0f, height, m_orthoOp.x, m_orthoOp.y);
    }
    break;

    }
  }

  void Camera::ImguiEditor()
  {
    static bool modeselection = false;
    static glm::vec3 targetDir(0.0f);
    float rot[] = { 0,0,0 };
    static float todegree = 180 / 3.1416f;
    ImGui::Begin("Camera editor");
    ImGui::Text("Rotation: %f %f %f", GetEuler().x, GetEuler().y*todegree, GetEuler().z*todegree);
    ImGui::DragFloat3("Rotation", rot, 0.1f);
    ImGui::DragFloat3("Camera proj:", (float*)&m_proj[3], 0.1f);
    ImGui::DragFloat3("Camera Position", (float*)&m_view[3], 0.1f);
    ImGui::Spacing();
    ImGui::DragFloat("FOV", &m_fov, 0.1f);
    ImGui::DragFloat("Near FOV", &m_nearFOV, 0.1f);
    ImGui::DragFloat("Far FOV", &m_farFOV, 0.1f);
    ImGui::Spacing();
    ImGui::DragFloat3("Target dir", (float*)&targetDir, 0.1f);
    ImGui::DragFloat2("Ortho Op", (float*)&m_orthoOp);
    ImGui::Checkbox("Ortho/Perspective", &modeselection);

    ImGui::End();
    Rotate(rot[0], glm::vec3(0.0f, 1.0f, 0.0f));
    Rotate(rot[1], glm::vec3(1.0f, 0.0f, 0.0f));
    Rotate(rot[2], glm::vec3(0.0f, 0.0f, 1.0f));
    SetFieldOfView(m_fov);

    m_mode = modeselection ? EMode::Orthograpic : EMode::Perspective;
  }
  //todo: remove from here
  glm::vec3 Camera::GetEuler()
  {
    glm::quat q = glm::quat_cast(m_view);


    return Mathf::ToEuler(q);;
  }
  void Camera::CameraInput(float speed)
  {

    if (Input::IsKeyPressed(GB_KEY_W))
    {
      m_pos += speed * m_front;
    }
    if (Input::IsKeyPressed(GB_KEY_S))
    {
      m_pos -= speed * m_front;
    }
    if (Input::IsKeyPressed(GB_KEY_A))
    {
      m_pos -= glm::normalize(glm::cross(m_front, m_up))* speed;
    }
    if (Input::IsKeyPressed(GB_KEY_D))
    {
      m_pos += glm::normalize(glm::cross(m_front, m_up))* speed;
    }
  }
}