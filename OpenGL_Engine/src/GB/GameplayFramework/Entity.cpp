#include "gbpch.h"
#include "Entity.h"
#include "imgui.h"
#include "Components/Transform.h"
GB::Entity::Entity(const std::string& name /*= "Entity"*/) :m_name(name), isEnabled(true)
{
	//every component has a transform reference
	Transform* transform = new Transform();
	AddComponent(*transform);
	
}
void GB::Entity::AddComponent(Component& component)
{
	m_components.push_back(&component);
}

void GB::Entity::RemoveComponent(Component& component)
{
	GB_CORE_ERROR("Not implemented");
}

void GB::Entity::UpdateComponents(float deltaTime)
{
	for (int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->OnUpdate(deltaTime);
	}
}

void GB::Entity::ImguiComponents()
{
	ImGui::Text("Name: %s", m_name);
	for (int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->ImguiRender();
	}
}



void GB::Entity::OnUpdate(float deltaTime)
{
	UpdateComponents(deltaTime);
}


//void GB::SpriteRenderer::ImguiRender()
//{
//	if (ImGui::CollapsingHeader("Sprite Renderer"))
//	{
// 		ImGui::Checkbox("FlipX", &this->flipX);
//		ImGui::Checkbox("FlipY", &this->flipY);
//		ImGui::Spacing();
//		ImGui::InputInt("Layer index", &this->layer);
//		ImGui::ColorPicker4("Color", (float*)&this->color);
//	}
//}
