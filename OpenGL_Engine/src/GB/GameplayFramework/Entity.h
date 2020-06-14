#pragma once
#include "GB\Core.h"
#include "gbpch.h"

#include "GB/Render/Texture2D.h"
#include "GB/Math.h"
#include "Components/Component.h"
//staticmeshactor
#include "GB/Render/Mesh.h"
#include "GB/Render/Renderer.h"
#include "GB/Utils/UniqueID.h"

namespace GB
{
	
	/*
	This class represent the base elements that can be spawned in the world.

	every Actor in the game has different methods that will be update in this sequence

	1. Awake
	2. Start
	3. Update Loop
	4. Render elements

	*/
	class Entity
	{
	public:

		Entity(const std::string& m_Name = "Entity");

		/*Called before start function*/
		virtual void OnAwake() {}
		/*Called when the object has start*/
		virtual void OnStart() {}
		/*Called every frame*/
		virtual void OnUpdate(float deltaTime);

		/*This is called when the actor is destroyed from the world*/
		virtual void OnDestroy() {}

		//todo: this is temp and will be changed in the future
		virtual void OnRender() {}

		//Components
		const char* GetName() { return m_name.c_str(); }
		void AddComponent(Component& component);
		void RemoveComponent(Component& component);
	protected:

		void UpdateComponents(float deltaTime);
		void ImguiComponents();

		/*the name of the object*/
		std::string m_name;
		/*all the tags that the object has associate*/
		std::vector<std::string> m_Tags;
		std::vector<Component*> m_components;
		bool isEnabled;
	};

}