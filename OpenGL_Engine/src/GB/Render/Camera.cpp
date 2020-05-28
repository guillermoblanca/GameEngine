#include "gbpch.h"
#include "Camera.h"
#include "GB\Application.h"
#include "imgui.h"
#include "GB\Input.h"
#include "GB\KeyCodes.h"

namespace GB
{
	Camera* Camera::s_main = new Camera();
	Camera::Camera() : m_ProjectionMatrix(glm::mat4(1.0f))
	{
		m_ViewMatrix = glm::mat4(1.0f);
		m_fov = 45.0f;
		m_nearFOV = 0.1f;
		m_farFOV = 100.0f;
		m_Rotation = 0.0f;
		
		s_main = this;
	}
	void Camera::SetMainCamera(Camera* camera)
	{
		s_main = camera;
	}


	glm::vec3 Camera::GetEuler()
	{
		glm::quat q = glm::quat_cast(m_ViewMatrix);
		return Mathf::ToEuler(q);;
	}
	void Camera::LookAt(vector3 position, float distance)
	{
		float camX = std::sin(Time::DeltaTime()) * distance;
		float camZ = std::cos(Time::DeltaTime()) * distance;
		m_ViewMatrix = glm::lookAt(glm::vec3(camX, 0.0f, camZ), position, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void Camera::Translate(vector3 pos)
	{
		m_Position = pos;
		RecalculateMatrix();
	}
	void Camera::Rotate(float degrees, vector3 direction)
	{
//		m_TargetView = direction;
	}
	void Camera::SetFieldOfView(float degree)
	{
		static float width = (float)Application::Get().GetWindow().GetWidth();
		static float height = (float)Application::Get().GetWindow().GetHeight();
		m_ProjectionMatrix = glm::perspective(glm::radians(m_fov), width / height, m_nearFOV, m_farFOV);
	}

	void Camera::RecalculateMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *	glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));
		m_ViewMatrix = transform;

	//	m_ViewMatrix = glm::lookAt(m_TargetView , m_Position, vector3(0, 1, 0));
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::ImguiEditor()
	{
		ImGui::Begin("Camera editor");
		ImGui::DragFloat3("Position", (float*)&m_Position, 0.1f);
		ImGui::DragFloat("Rotation", &m_Rotation, 0.1f);
		ImGui::Spacing();
		ImGui::DragFloat("FOV", &m_fov, 0.1f);
		ImGui::DragFloat("Near FOV", &m_nearFOV, 0.1f);
		ImGui::DragFloat("Far FOV", &m_farFOV, 0.1f);
		ImGui::End();
		
		SetFieldOfView(m_fov);

	}
	//todo: remove from here



	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), vector3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}
}