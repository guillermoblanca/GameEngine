#include "gbpch.h"
#include "Actor.h"
#include "imgui.h"
void GB::Actor::AddComponent(Component & component)
{
	m_components.push_back(&component);
}

void GB::Actor::RemoveComponent(Component & component)
{
	GB_CORE_ERROR("Not working");
}

void GB::Actor::UpdateComponent()
{
	for (int in = 0; in < m_components.size(); in++)
	{
		m_components[in]->Update();
	}
}

void GB::Actor::ImguiComponent()
{
	ImGui::Text("Name: %s", m_name);
	for (int in = 0; in < m_components.size(); in++)
	{
		m_components[in]->ImguiRender();
	}
}

//unsigned int GB::GameObject::ComponentCount()
//{
//	return m_components.size();
//}

void GB::SpriteRenderer::ImguiRender()
{
  if (ImGui::CollapsingHeader("Sprite Renderer"))
  {
    ImGui::Checkbox("FlipX", &this->flipX);
    ImGui::Checkbox("FlipY", &this->flipY);
    ImGui::Spacing();
    ImGui::InputInt("Layer index", &this->layer);
    ImGui::ColorPicker4("Color", (float*)&this->color);
  }
}

GB::Actor::Actor(const std::string& m_Name)
{
}
