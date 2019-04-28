#pragma once
#include "GB\Core.h"

#include "GB/Math.h"
namespace GB
{
	struct Transform
	{
		vector3 position;
		vector3 rotation;
		vector3 scale;

		Transform();
	
		void Translate(glm::vec3 pos);
		void Lerp(glm::vec3 init, glm::vec3 des, float dt);
		void Lerp0(glm::vec3 init, glm::vec3 des, float dt);

		void SetScale(glm::vec3 scl);
	
		void Rotate(glm::vec3 rot);

		matrix4 GetMat4();


	};
}