#include "gbpch.h"
#include "World.h"
#include "WorldManager.h"

namespace GB
{
	unsigned int World::ID = -1;

	World::World() : m_id(++ID)
	{

	}

	void World::SpawnEntity(Entity* actor, vector3 pos)
	{

		//here we will implement the addition to the different sistems

		actor->OnAwake();
		entities.push_back(actor);
		actor->OnStart();
	}

	bool World::Destroy(Entity* actor)
	{

		for (int i = 0; i < entities.size(); i++)
		{
			if (entities[i] == actor)
			{
				entities[i]->OnDestroy();
				entities.erase(entities.begin() + i);
				return true;
			}
		}

		return false;
	}

	void World::OnUpdate(float DeltaTime)
	{
		for (int i = 0; i < entities.size(); i++)
		{
			entities[i]->OnUpdate(DeltaTime);
		}
	}
}