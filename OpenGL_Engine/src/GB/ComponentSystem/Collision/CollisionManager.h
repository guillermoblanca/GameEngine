#pragma once

#include "GB\Core.h"
#include "GB\Math.h"
namespace GB
{
	struct BoxCollider
	{
		vector2 position;
		float width;
		float height;
	};
	class CollisionManager
	{
	private:
		//singleton
		//herencia de layer

	public:
		static bool CheckCollision(BoxCollider col, BoxCollider col2);
	};
}