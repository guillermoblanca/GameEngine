
#include "GB.h"
#include "imgui\imgui.h"


/*
TODO: Make console layer for debug, search if is best in gb or in sandbox

TODO: Make a editor project

*/
class LayerExample : public GB::Layer
{
public:

	void OnUpdate() override
	{


	}

	void OnImguiRender() override 
	{

		ImGui::Begin("Console");
		ImGui::Text("Hello world!");
		bool state = ImGui::Button("Clear console");
		if (state)
		{
			GB_CLIENT_INFO("Button pushed!");
		}
		ImGui::End();
	}

	void OnEvent(GB::Event& event) override
	{


		if (event.GetEventType() == GB::EventType::KeyPressed)
		{
			GB::KeyPressedEvent& e = (GB::KeyPressedEvent&) event;
			GB_CLIENT_TRACE("{0}", char(e.GetKeycode()));
		}
	}
};

class Sandbox : public GB::Application
{
public:
	Sandbox()
	{
		GB_CLIENT_INFO("Client info");

		PushLayer(new LayerExample());
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
