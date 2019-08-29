#pragma once
#include "GB\Core.h"
#include "gbpch.h"

#include "GB/Render/Texture2D.h"
#include "GB/Math.h"
namespace GB
{
	class Component
	{
	public:

		virtual void Update()=0;
		virtual void ImguiRender()=0;
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
	class GameObject
	{
	private:
		
		std::string m_name;
		unsigned int m_componentIndex;
	public:
		std::vector<Component*> m_components;
		inline std::string GetName() { return m_name; }
		GameObject(std::string name) : m_name(name), m_componentIndex(0){}

		void AddComponent(Component& component);
		void RemoveComponent(Component& component);

		void UpdateComponent();
		void ImguiComponent();
		//unsigned int ComponentCount();

		//Component* GetComponent(Component& type);
	};
}