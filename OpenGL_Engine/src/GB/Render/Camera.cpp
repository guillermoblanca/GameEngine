#include "gbpch.h"
#include "Camera.h"
#include "GB\Application.h"
#include "glm\gtc\matrix_transform.hpp"
#include "imgui.h"
namespace GB
{
	glm::mat4 Camera::m_proj = glm::mat4(1.0f);
	glm::mat4 Camera::m_view = glm::mat4(1.0f);
	glm::vec2 Camera::m_orthoOp = glm::vec2(-1.0f,1.0f);
	float Camera::radius = 10;
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
			m_proj = glm::ortho(0.0f, width, 0.0f, height,m_orthoOp.x,m_orthoOp.y);
		}
		break;

		}
	}

	void Camera::ImguiEditor()
	{
		static bool option = false;
		static glm::vec3 targetDir(0.0f);
		 float rot[] = { 0,0,0 };

		ImGui::Begin("Camera editor");
		ImGui::DragFloat3("Camera proj:", (float*)&m_proj[3],0.1f);
		ImGui::DragFloat3("Camera Position", (float*)&m_view[3],0.1f);
		ImGui::DragFloat3("Rotation", rot, 0.1f);
		ImGui::Spacing();
		ImGui::DragFloat3("Target dir", (float*)&targetDir,0.1f);
		ImGui::DragFloat("Radius", &radius);
		ImGui::Spacing();
		ImGui::DragFloat("FOV", &m_fov, 0.1f);
		ImGui::DragFloat2("Ortho Op", (float*)&m_orthoOp);
		ImGui::Checkbox("Ortho/Perspective", &option);
		ImGui::End();

		Rotate(rot[0],glm::vec3(1.0f,0.0f,0.0f));
		Rotate(rot[1],glm::vec3(0.0f,1.0f,0.0f));
		Rotate(rot[2],glm::vec3(0.0f,0.0f,1.0f));
		SetFieldOfView(m_fov);

		m_mode = option ? Mode::Ortho : Mode::Perspective;
	}
}