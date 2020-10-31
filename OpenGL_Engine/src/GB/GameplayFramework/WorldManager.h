#pragma once
#include "GB/Layer.h"
#include "World.h"

namespace GB
{

	class WorldManager : public Layer
	{
		
	public:
		WorldManager();
		~WorldManager();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& e) override;
		virtual void OnImguiRender() override;

		
	//	static bool Save(std::string filepath, const World& world);
	//	static bool Load(std::string filePath, const World& world);
   
		//static World* Create();
		World* GetActiveWorld();

	private:

		World* world;
	};
}