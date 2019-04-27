#pragma once

#include "GB\Core.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "GB\Time.h"
namespace GB
{
	class GBAPI Camera
	{
	public:
		enum Mode { Ortho,Perspective};
		
		static void Translate(glm::vec3 pos);
		static void Rotate(float degrees, glm::vec3 direction);
		static void SetFieldOfView(float degree);
		static void LookAt(glm::vec3 position,float distance);

		static void ImguiEditor();

		static glm::vec3 GetEuler();
		static inline float GetFOV() { return m_fov; }
		static inline glm::mat4 GetProj() { return m_proj; }
		static inline glm::mat4 GetView() { return m_view; }

		static inline glm::vec3 GetRot() { return glm::vec3(0.0f); }

		static void CameraInput(float speed);
		static Mode m_mode;
	private:

		static glm::vec3 m_pos;
		static glm::vec3 m_front;
		static glm::vec3 m_up;

		static glm::mat4 m_proj;
		static glm::mat4 m_view;
		static float m_fov;
		static glm::vec2 m_orthoOp;

	};
}