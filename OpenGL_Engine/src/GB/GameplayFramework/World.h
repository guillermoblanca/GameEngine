#pragma once
#include "GB/GameplayFramework/GameObject.h"
#include "GB/Core.h"
#include "gbpch.h"
namespace GB
{
	class World
	{
		friend Actor;
	public:

		void Instantiate(Actor* actor, vector3 pos);
		void Instantiate(Actor* actor, vector3 pos,vector3 rot);
		void Instantiate(Actor* actor, vector3 pos,vector3 rot,Actor* parent);

		
	private:
		std::vector<Actor*> actors;
		
	};
}