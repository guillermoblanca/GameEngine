#pragma once
#include "GB\Core.h"
#include "gbpch.h"

#include "GB/Render/Texture2D.h"
#include "GB/Math.h"

//staticmeshactor
#include "GB/Render/Mesh.h"
#include "GB/Render/Renderer.h"
namespace GB
{
	class Component
	{
	public:

		virtual void Update() = 0;
		virtual void ImguiRender() = 0;

		bool operator ==(const Component& other)
		{
			return other.ID == ID;
		}

	protected:

		int ID;
	};

	class SpriteRenderer : public Component
	{
	public:

		std::unique_ptr<Texture2D> sprite;
		bool flipX;
		bool flipY;
		color color;
		int layer;


		void ImguiRender();
	};

	/*
	This class represent the base elements that can be spawned in the world.

	every Actor in the game has different methods that will be update in this sequence

	1. Awake
	2. Start
	3. Update Loop
	4. Render elements

	*/
	class Actor
	{
	public:

		Actor(const std::string& m_Name);

		/*Called before start function*/
		virtual void Awake() = 0;
		/*Called when the object has start*/
		virtual void Start() = 0;
		/*Called every frame*/
		virtual void Update(float deltaTime) = 0;

		/*This is called when the actor is destroyed from the world*/
		virtual void Destroy() = 0;

		/*Called when the object is being renderer in the screen*/
		virtual void OnBeginRender() = 0;
		/*Callen when the object is not being renderer in the screen*/
		virtual void OnEndRender() = 0;

		//Components

		void AddComponent(Component& component);
		void RemoveComponent(Component& component);

		void UpdateComponent();
		void ImguiComponent();

	private:
		/*the name of the object*/
		std::string m_name;
		/*all the tags that the object has associate*/
		std::vector<std::string> m_Tags;
		std::vector<Component*> m_components;
		bool isEnabled;

	};

	class StaticMeshActor : public Actor
	{
	public:

		StaticMeshActor(Mesh* meshModel) :Actor("StaticMeshActor"), mesh(meshModel)
		{
			/*		RenderObject* render = new RenderObject("New StaticMeshActor");
					render->Create(*mesh);
					render->m_textureID = 0;
					Renderer::Get().PushObj(render);*/
		}
		Mesh* mesh;
	private:
	};
}