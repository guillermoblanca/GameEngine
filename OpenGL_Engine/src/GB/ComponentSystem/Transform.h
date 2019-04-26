#pragma once
#include "GB\Core.h"

#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"
namespace GB
{
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		Transform();
	
		void Translate(glm::vec3 pos);
		void Lerp(glm::vec3 pos, float dt);

		void SetScale(glm::vec3 scl);
	
		void Rotate(glm::vec3 rot);

		glm::mat4 GetMat4();


	};
}