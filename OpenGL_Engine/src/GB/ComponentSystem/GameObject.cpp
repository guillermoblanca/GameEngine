#include "gbpch.h"
#include "GameObject.h"
#include "imgui.h"
void GB::GameObject::AddComponent(Component & component)
{
	m_components.push_back(&component);
}

void GB::GameObject::RemoveComponent(Component & component)
{
	GB_CORE_ERROR("Not working");
}

void GB::GameObject::UpdateComponent()
{
	for (int in = 0; in < m_components.size(); in++)
	{
		m_components[in]->Update();
	}
}

void GB::GameObject::ImguiComponent()
{
	ImGui::Text("Name: %s", m_name.c_str());
	for (int in = 0; in < m_components.size(); in++)
	{
		m_components[in]->ImguiRender();
	}
}

//unsigned int GB::GameObject::ComponentCount()
//{
//	return m_components.size();
//}


