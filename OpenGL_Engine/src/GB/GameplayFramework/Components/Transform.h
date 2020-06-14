#pragma once
#include "Component.h"
#include "GB/Math.h"

namespace GB
{
	class Transform : public Component
	{
	public:

		Transform();

		vector3 position;
		float pitch, yaw, roll;
		vector3 scale;

		void Translate(const vector3& pos);
		/*Rotates de objPos around position*/
		void RotateAround(const vector3& objpos, float radius, float dt);
		void Lerp(const vector3& init,const vector3& des, float dt);
		void Lerp0(const vector3& init,const vector3& des, float dt);

		void SetScale(const vector3& scl);
		void SetScale(float scl);
		void Rotate(const vector3& rot);

		matrix4 GetMat4();

		void OnUpdate(float DeltaTime) override;
		void ImguiRender() override;

	};

}