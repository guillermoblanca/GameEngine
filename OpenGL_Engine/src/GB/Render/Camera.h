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
		
		static void Translate(vector3 pos);
    static inline vector3 Position() { return m_view[3]; }
		static void Rotate(float degrees, vector3 direction);
		static void SetFieldOfView(float degree);
		static void LookAt(vector3 position,float distance);

		static void ImguiEditor();

		static vector3 GetEuler();
		static inline float GetFOV() { return m_fov; }
		static inline matrix4 GetProj() { return m_proj; }
		static inline matrix4 GetView() { return m_view; }

		static inline vector3 GetRot() { return vector3(0.0f); }

		static void CameraInput(float speed);

		void SetCameraMode(Camera camera, EMode mode)
		{
			vector3 distance = camera.target - camera.position;
			cameratargetdistance = glm::length(distance);
		}
		void UpdateCamera(Camera *camera);

	private:

		static EMode m_mode;
    static vector3 m_pos;
		static vector3 m_front;
		static vector3 m_up;

		static matrix4 m_proj;
		static matrix4 m_view;

		static float m_fov;
    static float m_nearFOV;
    static float m_farFOV;

		static vector2 m_orthoOp;

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