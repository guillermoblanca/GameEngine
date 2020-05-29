#pragma once
#include "GB.h"
#include "imgui/imgui.h"

class FreeCamera : public GB::Layer
{
private:
	float timer = 0;
	vector3 prevMouse = { 0,0 ,0};
	float distance = 10;
	float m_RotSpeed = 1.2f;
	float m_MovSpeed = 0.1f;
	vector3 m_Direction = vector3(0, 0, 0);
	//temp
	GB::EditorMenu editor;
	bool shouldUpdate = true;
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
