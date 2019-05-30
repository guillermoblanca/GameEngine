#include "gbpch.h"
#include "CollisionManager.h"

namespace GB
{
	bool CollisionManager::CheckCollision(BoxCollider col, BoxCollider col2) 
	{
		//https://tutorialedge.net/gamedev/aabb-collision-detection-tutorial/
		bool A = col.position.x < col2.position.x + col2.width;
		bool A2 = col.position.x + col.width > col2.position.x;
		bool B = col.position.y < col2.position.y + col2.height;
		bool B2 = col.position.y +col.height > col2.position.y;
		return	A && A2 && B && B2;
	}
}