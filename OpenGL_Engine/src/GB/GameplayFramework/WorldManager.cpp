#pragma once
#include "gbpch.h"
#include "imgui.h"
#include "WorldManager.h"

namespace GB
{

	WorldManager::WorldManager() : Layer("WorldManager"),world(new World())
	{
	}


	WorldManager::~WorldManager()
	{

	}

	void WorldManager::OnAttach()
	{

	}

	void WorldManager::OnDetach()
	{

	}

	void WorldManager::OnUpdate(/*Add deltaTime*/)
	{
		GB_CORE_TRACE("On update called from worldmanager");


		//todo: we should change this in the layer system
		world->OnUpdate(Time::DeltaTime());

	}

	void WorldManager::OnEvent(Event& e)
	{

	}

	void WorldManager::OnImguiRender()
	{
		ImGui::Begin("Hierarchy");
		
		ImGui::Text(world->m_name.c_str());
		for (int i = 0; i < world->entities.size(); i++)
		{
			ImGui::Text(world->entities[i]->GetName());
		}

		ImGui::End();
	}

	GB::World* WorldManager::GetActiveWorld()
	{
		return world;
	}

}