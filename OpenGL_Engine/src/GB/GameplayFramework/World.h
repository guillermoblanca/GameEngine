#pragma once
#include "GB/GameplayFramework/Actor.h"
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
		
		void Destroy(Actor* actor);
		void Destroy(Actor* actor, float delay);

		Actor* GetActorByName(const std::string& name);
		Actor* GetActorByTag(const std::string& name);
		const Actor** GetActorsByTag(const std::string& name);

		bool LineTraceByObject(vector3 start, vector3 end,HitInfo, Actor* outActor);
	private:
		std::vector<Actor*> actors;
		
	};

	struct HitInfo
	{
		//physics caracteristics
	};
}