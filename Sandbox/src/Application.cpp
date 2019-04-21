
#include "GB.h"
#include "imgui\imgui.h"
using namespace GB;
typedef std::pair<float, float> vector2;
class FreeCamera : public GB::Layer
{
private:
	vector2 mouse;
	vector2 prevMouse = { 0,0 };
	float velocity = 0.01f;
public:

	vector2 CameraDirection()
	{
		mouse = Input::GetMousePosition();

		vector2 diff = { mouse.first - prevMouse.first,mouse.second - prevMouse.second };
		diff.first = diff.first > 1 ? 1 : diff.first < -1 ? -1 : diff.first;
		diff.second = diff.second > 1 ? 1 : diff.second < -1 ? -1 : diff.second;

		prevMouse = mouse;
		return diff;
	}
	void OnUpdate() override
	{

		unsigned int id = 1;
		if (Input::IsKeyPressed(GB_KEY_W))
		{
			Renderer::Get().m_renderObjects[id]->m_transform = glm::translate(Renderer::Get().m_renderObjects[id]->m_transform, glm::vec3(0.0f, velocity, 0.0f));
		}
		if (Input::IsKeyPressed(GB_KEY_S))
		{
			Renderer::Get().m_renderObjects[id]->m_transform = glm::translate(Renderer::Get().m_renderObjects[id]->m_transform, glm::vec3(0.0f, -velocity, 0.0f));
		}
		if (Input::IsKeyPressed(GB_KEY_A))
		{
			Renderer::Get().m_renderObjects[id]->m_transform = glm::translate(Renderer::Get().m_renderObjects[id]->m_transform, glm::vec3(-velocity, 0.0f, 0.0f));

		}
		if (Input::IsKeyPressed(GB_KEY_D))
		{
			Renderer::Get().m_renderObjects[id]->m_transform = glm::translate(Renderer::Get().m_renderObjects[id]->m_transform, glm::vec3(velocity, 0.0f, 0.0f));

		}
		if (Input::IsKeyPressed(GB_KEY_Q))
		{
			Renderer::Get().m_renderObjects[id]->m_transform = glm::translate(Renderer::Get().m_renderObjects[id]->m_transform, glm::vec3(0.0f, 0.0f, -velocity));

		}
		if (Input::IsKeyPressed(GB_KEY_E))
		{
			Renderer::Get().m_renderObjects[id]->m_transform = glm::translate(Renderer::Get().m_renderObjects[id]->m_transform, glm::vec3(0.0f, 0.0f, velocity));

		}
		if (GB::Input::IsMousePressed(1))
		{

			vector2 diff = CameraDirection();

			GB::Camera::Translate(glm::vec3(diff.first*Time::DeltaTime()*velocity, 0.0f, diff.second*Time::DeltaTime()*velocity));
			GB_CORE_WARN("DIFF: {0},{1}", diff.first, diff.second);
		}
	}

	void OnImguiRender() override
	{

		GB::Camera::ImguiEditor();
		ImGui::Begin("Values");
		ImGui::Text("Time: %2f", GB::Time::DeltaTime());
		ImGui::Text("Mouse %2f,%2f", mouse.first, mouse.second);
		ImGui::DragFloat("Velocity", &velocity);
		ImGui::End();
	}
	void OnEvent(GB::Event& event) override
	{
		if (event.GetEventType() == GB::EventType::KeyPressed)
		{
			GB::MouseButtonPressedEvent& e = (GB::MouseButtonPressedEvent&) event;

			GB_CLIENT_TRACE("{0}", (e.ToString()));
		}
	}
};

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
