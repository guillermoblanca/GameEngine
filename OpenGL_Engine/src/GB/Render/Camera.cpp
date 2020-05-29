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
		m_Pitch =m_Yaw =m_Roll = 0.0f;
		
		m_Direction = glm::normalize(m_Position - m_Target);

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
//		m_ViewMatrix = glm::lookAt(glm::vec3(camX, 0.0f, camZ),glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void Camera::SetPosition(const vector3& position)
	{
		m_Position = position;
		RecalculateMatrix();
	}
	void Camera::SetRotation(float pitch, float yaw, float roll)
	{
		m_Pitch = pitch;
		m_Yaw = yaw;
		m_Roll = roll;
	}
	void Camera::SetFieldOfView(float degree)
	{
		static float width = (float)Application::Get().GetWindow().GetWidth();
		static float height = (float)Application::Get().GetWindow().GetHeight();
		m_ProjectionMatrix = glm::perspective(glm::radians(m_fov), width / height, m_nearFOV, m_farFOV);
	}

	void Camera::RecalculateMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position)*
			glm::rotate(glm::mat4(1.0f), m_Pitch, glm::vec3(1, 0, 0));

		transform = glm::rotate(transform, m_Yaw, glm::vec3(0, 1, 0));
		transform = glm::rotate(transform, m_Roll, glm::vec3(0, 0, 1));

		//m_ViewMatrix = transform;
		vector3 cameraFront = vector3(0.0f, 0.0f, 1.0f);
		vector3 direction;
		direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		direction.y = sin(glm::radians(m_Pitch));
		direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		cameraFront = glm::normalize(direction);


		vector3 cameraUp = vector3(0, 1, 0);
		m_ViewMatrix = glm::lookAt(m_Position,m_Position + cameraFront,cameraUp);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::ImguiEditor()
	{
		float m_Rotation[3] = { m_Pitch,m_Yaw,m_Roll };
		ImGui::Begin("Camera editor");
		ImGui::DragFloat3("Position", (float*)&m_Position, 0.1f);
		ImGui::DragFloat3("Rotation", m_Rotation, 0.1f);
		ImGui::Spacing();
		ImGui::DragFloat("FOV", &m_fov, 0.1f);
		ImGui::DragFloat("Near FOV", &m_nearFOV, 0.1f);
		ImGui::DragFloat("Far FOV", &m_farFOV, 0.1f);
		ImGui::End();
		
		m_Pitch= m_Rotation[0];
		m_Yaw  = m_Rotation[1];
		m_Roll = m_Rotation[2];
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