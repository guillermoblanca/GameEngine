#pragma once
#include "gbpch.h"
#include "GB/Render/RenderObject.h"
#include "GB/Core.h"

/*
World
World Manager can change level and add additive to it

*World instance of the level 
Has a reference ob all objects of the game

instantia actors
destroy actors
get actos
find actor by name

*/

namespace GB
{
	//TODO: change this to a own class
	typedef RenderObject Actor;


	static World* GetWorld();

	class World
	{
	public:

		Actor* FindActorByName(const std::string& actorName);

		virtual bool Create(std::string path);
		virtual bool Create(const std::vector<Actor*>& actors);

		virtual void Init();
		virtual void ShutDown();

		virtual void Instantiate(Actor& spawnActor, vector3 position);
		virtual void Instantiate(Actor& spawnActor, vector3 position, quaternion rotation);
		virtual void Instantiate(Actor& spawnActor, vector3 position, quaternion rotation, Actor* parent);

		virtual void Destroy(Actor& actor);

		virtual void OnLevelLoaded();
		virtual void OnLevelUnLoaded();

	private:
		std::vector<Actor*> m_actors; //actors in the level
		std::string m_levelName; //level name
		float m_realtimeSeconds; //time since level start

		bool m_isAditive;
		bool m_isLoaded;
	};

	

	//Singleton class that can spawn levels and loaded
	class WorldManager
	{
	public:

	private:
		std::vector<World*> m_activeWorlds;

	};
}