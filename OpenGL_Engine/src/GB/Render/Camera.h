#pragma once

#include "GB\Core.h"
#include "GB\Math.h"
#include "GB\Time.h"
#include "glm/glm.hpp"
namespace GB
{
	class GBAPI Camera
	{
	public:
		enum EMode { Perspective = 0, Orthograpic };
		Camera();

		void Translate(vector3 pos);
		void Rotate(float degrees, vector3 direction);
		void SetFieldOfView(float degree);
		void LookAt(vector3 position, float distance);


		inline vector3 Position() { return m_ViewMatrix[3]; }
		vector3        GetEuler();
		inline float   GetFOV() { return m_fov; }
		inline matrix4 GetProjectionMatrix() { RecalculateMatrix(); return m_ProjectionMatrix; }
		inline matrix4 GetViewMatrix() { RecalculateMatrix(); return m_ViewMatrix; }
		inline matrix4 GetProjectionViewMatrix() { RecalculateMatrix(); return m_ProjectionViewMatrix; }

		void ImguiEditor();
		void SetMainCamera(Camera* camera);
		void RecalculateMatrix();

		inline static Camera* GetMain() { return s_main; }


	private:

		static Camera* s_main;

		matrix4 m_ProjectionMatrix;
		matrix4 m_ViewMatrix;
		matrix4 m_ProjectionViewMatrix;
		vector3 m_Position;
		vector3 m_TargetView = { 0.0f,0.0f,0.0f };


		float m_Rotation;

		float m_fov;
		float m_nearFOV;
		float m_farFOV;

		vector3 target; //Camera target it looks at;
	};



	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);

		const vector3& GetPosition()const { return m_Position; }
		void SetPosition(const vector3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }


		inline const glm::mat4& GetProjectionMatrix()const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix()const;
		const glm::mat4& GetViewProjectionMatrix()const;
	private:
		void RecalculateViewMatrix();

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		vector3 m_Position = { 0.0f,0.0f,0.0f };
		float m_Rotation = 0.0f;


	};



}
/*

Camera orientation
Camera position

Perspective/Orthographic
FOV
Aspect Ratio

*/