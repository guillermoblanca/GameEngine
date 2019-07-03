#pragma once

#include "GB\Core.h"
#include "GB\Math.h"
#include "GB\Time.h"
namespace GB
{
	class GBAPI Camera
	{
	public:
		enum EMode { Perspective = 0,Orthograpic};
		
		void Translate(vector3 pos);
    inline vector3 Position() { return m_view[3]; }
		void Rotate(float degrees, vector3 direction);
		void SetFieldOfView(float degree);
		void LookAt(vector3 position,float distance);

		void ImguiEditor();
    
		vector3 GetEuler();
		inline float GetFOV() { return m_fov; }
		inline matrix4 GetProj() { return m_proj; }
		inline matrix4 GetView() { return m_view; }

		inline vector3 GetRot() { return vector3(0.0f); }

		static void CameraInput(float speed);

		void SetCameraMode(Camera camera, EMode mode)
		{
			vector3 distance = camera.target - camera.position;
			cameratargetdistance = glm::length(distance);
		}
		void UpdateCamera(Camera *camera);

	private:

		EMode m_mode;
    vector3 m_pos;
		vector3 m_front;
		vector3 m_up;

		matrix4 m_proj;
		matrix4 m_view;

		float m_fov;
    float m_nearFOV;
    float m_farFOV;

		vector2 m_orthoOp;

		// NEW FEATURE

		const float mouse_sensitivity =0.003f;
		const float mouse_scroll_sensitivity = 1.5f;

		vector3 position; //Camera position
		vector3 target; //Camera target it looks at;
		vector3 up; //Camera up vector rotation over its axis
		float fov; //Camera field-of-view in y (degrees) in pespective mode
		EMode cameraMode;
		float cameratargetdistance = 0.0f;
	};
}