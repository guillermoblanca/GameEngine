#pragma once
#include "GB\Core.h"
#include "Component.h"
#include "GB/Math.h"
namespace GB
{
	struct Transform : Component
	{
		Transform() : Component("Transform"),position(0.0f), rotation(0.0f), scale(1.0f) {}
		vector3 position;
		vector3 rotation;
		vector3 scale;

	
		void Translate(glm::vec3 pos);
		void Lerp(glm::vec3 init, glm::vec3 des, float dt);
		void Lerp0(glm::vec3 init, glm::vec3 des, float dt);

		void SetScale(glm::vec3 scl);
	
		void Rotate(glm::vec3 rot);

		matrix4 GetMat4();


	};
}