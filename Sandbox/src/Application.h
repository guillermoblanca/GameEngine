#pragma once
#include "GB.h"
typedef std::pair<float, float> vector2;

class FreeCamera : public GB::Layer
{
private:
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

class Sandbox : public GB::Application
{
public:
	Sandbox()
	{
		GB_CLIENT_INFO("Client info");

		PushLayer(new LayerExample());
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
