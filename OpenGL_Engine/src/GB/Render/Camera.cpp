#include "gbpch.h"
#include "Camera.h"
#include "GB\Application.h"
#include "glm\gtc\matrix_transform.hpp"
namespace GB
{
	glm::mat4 Camera::m_proj = glm::mat4(1.0f);
	glm::mat4 Camera::m_view = glm::mat4(1.0f);

	float Camera::m_fov = 45.0f;
	Camera::Mode Camera::m_mode = Mode::Perspective;
	void Camera::Translate(glm::vec3 pos)
	{
		m_view = glm::translate(m_view, pos);
	}
	void Camera::Rotate(float degrees, glm::vec3 direction)
	{

		m_view = glm::rotate(m_view, glm::radians(degrees), direction);

	}
	void Camera::SetFieldOfView(float degree)
	{
		static float width = (float)Application::Get().GetWindow().GetWidth();
		static float height = (float)Application::Get().GetWindow().GetHeight();
		switch (m_mode)
		{
		case GB::Camera::Perspective:
		{

			m_proj = glm::perspective(glm::radians(m_fov), width / height, 0.1f, 100.0f);
		}
		break;
		case GB::Camera::Ortho:
		{
			m_proj = glm::ortho(0.0f, width, 0.0f, height,-1.0f,1.0f);
		}
		break;

		}
	}

	void Camera::ImguiEditor()
	{
		 float pos[] = { 0,0,0 };
		 float rot[] = { 0,0,0 };

		 auto proj = Camera::GetProj();
		 auto view = Camera::GetView();
		ImGui::Begin("Camera editor");
		ImGui::Text("Camera proj: %2f,%2f,%2f", proj[0].x, proj[1].y, proj[2].z);
		ImGui::Text("Camera view: %2f,%2f,%2f", view[0].x, view[1].y, view[2].z);
		ImGui::DragFloat3("Position", pos, 0.1f);
		ImGui::DragFloat3("Rotation", rot, 0.1f);
		ImGui::DragFloat("FOV", &m_fov, 0.1f);
		ImGui::End();

		Rotate(rot[0],glm::vec3(1.0f,0.0f,0.0f));
		Rotate(rot[1],glm::vec3(0.0f,1.0f,0.0f));
		Rotate(rot[2],glm::vec3(0.0f,0.0f,1.0f));
		Translate(glm::vec3(pos[0], pos[1], pos[2]));
		SetFieldOfView(m_fov);
	}
}