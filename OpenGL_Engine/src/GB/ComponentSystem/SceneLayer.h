#pragma once
#include "gbpch.h"
#include "GB\Core.h"
#include "GameObject.h"
#include "GB\Layer.h"
namespace GB
{
	class GBAPI SceneLayer : public  Layer
	{
	public:
		SceneLayer();

		void OnUpdate() override;
		inline void AddGameObject(GameObject* object) { m_gameobjects.push_back(object); }
		void RemoveGameObject(GameObject* object) {}//todo: make it

	private:
		bool isLoaded;
		std::string m_path;
		std::vector<GameObject*> m_gameobjects;
	};
}