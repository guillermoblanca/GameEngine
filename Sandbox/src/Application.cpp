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
		GB::MouseScrolledEvent& e = (GB::MouseScrolledEvent&) event;
	}
}


#pragma region FreeCamera


vector2 FreeCamera::CameraDirection()
{
	mouse = GB::Input::GetMousePosition();
	vector2 diff = mouse - prevMouse;

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
	RenderObject* obj = (RenderObject*)Renderer::Get().GetRenderobj(id);


	timer += Time::DeltaTime();
	obj->m_transform.Lerp0(glm::vec3(0.0f, 0.0f, 0.0f), destiny, std::abs(std::sin(timer)));

	Camera::CameraInput(velocity);
	if (GB::Input::IsMousePressed(1))
	{

		vector2 diff = CameraDirection();
		GB::Camera::Translate(glm::vec3(diff.x*velocity,- diff.y*velocity,0.0f ));
	}

	if (GB::Input::IsMousePressed(2))
	{
		float diff = CameraDirection().y;
		GB::Camera::Translate(glm::vec3(0.0f,0.0f,diff *velocity*2));

	}

	if (Input::IsKeyPressed(GB_KEY_LEFT_ALT) && Input::IsMousePressed(0))
	{
		vector2 position = CameraDirection();

		
		GB_CORE_INFO("Pivot point {0}",position);
		GB::Camera::Rotate(position.x, glm::vec3(0.f, 1.0f, 0.0f));
		GB::Camera::Rotate(position.y, glm::vec3(1.f, 0.0f, 0.0f));
	}
}

void FreeCamera::OnImguiRender()
{
	static int rendermode = 4;

	RenderObject* obj = (RenderObject*)Renderer::Get().GetRenderobj(1);
	GB::Camera::ImguiEditor();
	ImGui::Begin("Values");
	ImGui::Text("Time: %2f", timer);
	ImGui::Text("Deltatime: %2f", Time::DeltaTime());
	ImGui::Text("Mouse %2f,%2f", CameraDirection().x, CameraDirection().y);
	ImGui::DragFloat("Camera distance", &distance);
	ImGui::DragFloat("Velocity", &velocity);
	ImGui::DragFloat3("Destiny", (float*)&destiny);
	if (ImGui::Button("LookAt")) Camera::LookAt(obj->m_transform.position, distance);
	ImGui::DragInt("RenderMode", &rendermode, 1, 0, (int)GB::Renderer::RenderMode::Triangles);
	
	Renderer::Get().SetRenderMode(GB::Renderer::RenderMode(rendermode));

	ImGui::End();
}

void FreeCamera::OnEvent(GB::Event & event)
{
	if (event.GetEventType() == GB::EventType::MouseScrolled)
	{

		GB::MouseScrolledEvent& e = (GB::MouseScrolledEvent&) event;
	}

}


#pragma endregion

