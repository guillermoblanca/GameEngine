#pragma once
#include "gbpch.h"
#include "imgui.h"
#include "WorldManager.h"

namespace GB
{

	WorldManager::WorldManager() : Layer("WorldManager"), world(new World())
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

	void WorldManager::OnUpdate(TimeStep ts)
	{
		GB_CORE_TRACE("On update called from worldmanager");
		world->OnUpdate(ts);

	}

	void WorldManager::OnEvent(Event& e)
	{

	}

	void WorldManager::OnImguiRender()
	{
		ImGui::Begin("Hierarchy");

		ImGui::Text(world->m_name.c_str());

		if (ImGui::TreeNode("Base"))
		{
			ImGui::Indent();
			ImGui::Text("Slots ");
			ImGui::Text("Count");
			ImGui::Unindent();
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Slots"))
		{
			ImGui::TreePop();
		}

		for (int i = 0; i < world->entities.size(); i++)
		{
			auto entity = world->entities[i];
			if (ImGui::TreeNode(entity->GetName()))
			{
				ImGui::Indent();
				auto components = entity->GetComponents();
				for (int y = 0; y < components.size(); y++)
				{
					if (ImGui::TreeNode(components[y]->GetName().c_str()))
					{
						ImGui::Indent();
						components[y]->ImguiRender();
						ImGui::Unindent();
						ImGui::TreePop();

					}
				}
				ImGui::Unindent();
				ImGui::TreePop();
			}
		}

		ImGui::End();
	}

	GB::World* WorldManager::GetActiveWorld()
	{
		return world;
	}

}