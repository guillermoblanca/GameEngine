#pragma once
#include "GB/GameplayFramework/Entity.h"
#include "GB/Core.h"
#include "gbpch.h"

class WorldManager;

namespace GB
{

	class World
	{
		friend Entity;
	public:
		World();
		
		void SpawnEntity(Entity* actor, vector3 pos);
		/*void SpawnActor(Actor* actor, vector3 pos,vector3 rot);
		void SpawnActor(Actor* actor, vector3 pos,vector3 rot,Actor* parent);*/

		bool Destroy(Entity* actor);
		//void Destroy(Actor* actor, float delay);

	/*	Actor* GetActorByName(const std::string& name);
		Actor* GetActorByTag(const std::string& name);
		const Actor** GetActorsByTag(const std::string& name);*/

		//bool LineTraceByObject(vector3 start, vector3 end,HitInfo, Actor* outActor);
	//private:

		void OnUpdate(float DeltaTime);
		std::vector<Entity*> entities;
		std::string m_name;
		unsigned int m_id;
		static unsigned int ID;
	};

}