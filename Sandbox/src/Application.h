#pragma once
#include "GB.h"
#include "imgui/imgui.h"

class FreeCamera : public GB::Layer
{
private:
	glm::vec3 destiny= glm::vec3(3.0f,0.0f,0.0f);
	float timer = 0;
	vector2 mouse;
	vector2 prevMouse = { 0,0 };
	float distance = 10;
	float velocity = 0.01f;
public:

	vector2 CameraDirection();

	void OnAttach() override;
	void OnUpdate() override;

	void OnImguiRender() override;
	void OnEvent(GB::Event& event) override;
};

class LayerExample : public GB::Layer
{
public:

	void OnUpdate() override
	{


	}

	void OnImguiRender() override;

	void OnEvent(GB::Event& event) override;
};

class GameSystem : public GB::Layer
{
private:
	static GameSystem* m_instance;
public:
	inline static GameSystem* Instance() { return m_instance; }
	std::vector<GB::GameObject*> m_gameObjects;

	void AddGameObject(GB::GameObject& gameObject);
	void OnUpdate() override
	{
		for (size_t i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->UpdateComponent();
		}
	}

	void OnImguiRender() override
	{
    if (ImGui::Begin("Inspector"))
    {
      if (ImGui::Button("Add GameObject"))
      {
        AddGameObject(GB::GameObject("instance 1"));
      }
      for (size_t i = 0; i < m_gameObjects.size(); i++)
      {
        m_gameObjects[i]->ImguiComponent();
      }
      ImGui::End();
    }
	}
};


class Sandbox : public GB::Application
{
public:
	Sandbox()
	{
		GB_CLIENT_INFO("Client info");

//		PushLayer(new LayerExample());
		PushLayer(new GameSystem());
		PushLayer(new FreeCamera());
	}

	~Sandbox()
	{
		PopLayer(new GB::ImGuiLayer());
	}

};

GB::Application * GB::CreateApplication()
{
	return new Sandbox();
}
