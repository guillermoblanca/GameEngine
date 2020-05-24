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

	//temp
	GB::EditorMenu editor;
public:

	vector2 CameraDirection();

	void OnAttach() override;
	void OnUpdate() override;

	void UpdateCameraMovement();

	void OnImguiRender() override;
	void OnEvent(GB::Event& event) override;

};


class Sandbox : public GB::Application
{
public:
	Sandbox()
	{
		GB_CLIENT_INFO("Client info");

		PushLayer(new FreeCamera());
	}

	~Sandbox()
	{
	//	PopLayer(new GB::ImGuiLayer());
	}

};

GB::Application * GB::CreateApplication()
{
	return new Sandbox();
}
