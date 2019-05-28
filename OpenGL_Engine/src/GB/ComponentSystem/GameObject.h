#pragma once
#include "gbpch.h"
#include "GB/Core.h"
#include "Component.h"

namespace GB
{
	class GBAPI GameObject
	{
	public:
		GameObject();
		~GameObject();

		virtual void OnUpdate();
		virtual void OnRender();

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);
		Component* GetComponent(Component* componet);
	private:

		std::vector<Component*> m_components;
	};
}