#include "GB.h"
#include "Application.h"
#include "imgui\imgui.h"

using namespace GB;
void LayerExample::OnImguiRender()
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

void LayerExample::OnEvent(GB::Event & event)
{


	if (event.GetEventType() == GB::EventType::KeyPressed)
	{
		GB::KeyPressedEvent& e = (GB::KeyPressedEvent&) event;
		GB_CLIENT_TRACE("{0}", char(e.GetKeycode()));
	}
}


#pragma region FreeCamera


vector2 FreeCamera::CameraDirection()
{
	mouse = GB::Input::GetMousePosition();

	vector2 diff = { mouse.first - prevMouse.first,mouse.second - prevMouse.second };
	diff.first = diff.first > 1 ? 1 : diff.first < -1 ? -1 : diff.first;
	diff.second = diff.second > 1 ? 1 : diff.second < -1 ? -1 : diff.second;

	prevMouse = mouse;
	return diff;
}

void FreeCamera::OnAttach()
{
	Camera::Translate(glm::vec3(0.0f, 0.0f, -10.0f));
}

void FreeCamera::OnUpdate()
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

void FreeCamera::OnImguiRender()
{

	GB::Camera::ImguiEditor();
	ImGui::Begin("Values");
	ImGui::Text("Time: %2f", GB::Time::DeltaTime());
	ImGui::Text("Mouse %2f,%2f", mouse.first, mouse.second);
	ImGui::DragFloat("Velocity", &velocity);
	ImGui::End();
}

void FreeCamera::OnEvent(GB::Event & event)
{
	if (event.GetEventType() == GB::EventType::KeyPressed)
	{
		GB::MouseButtonPressedEvent& e = (GB::MouseButtonPressedEvent&) event;

		GB_CLIENT_TRACE("{0}", (e.ToString()));
	}
}


#pragma endregion

