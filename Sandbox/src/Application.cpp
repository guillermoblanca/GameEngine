#include "GB.h"
#include "gbpch.h"
#include "Application.h"
#include "imgui\imgui.h"
#include "GB/ImportTools/IO.h"
#include "glm/gtc/type_ptr.hpp"

using namespace GB;

vector2 FreeCamera::CameraDirection()
{
	return prevMouse;
}

void FreeCamera::OnAttach()
{
	GB_CLIENT_INFO("Initialized freecamera");

	std::vector<std::string> TexturePaths;
	TexturePaths.push_back("Assets/Texture/ball.png");
	TexturePaths.push_back("Assets/Texture/Brick.png");
	TexturePaths.push_back("Assets/Texture/Game.png");
	TexturePaths.push_back("Assets/Texture/lion-logo.png");

	std::vector<GB::Texture2D*> Textures;

	auto& renderer = Application::Get().GetRender();
	for (size_t i = 0; i < TexturePaths.size(); i++)
	{
		renderer->m_textures.push_back(Texture2D::Create(TexturePaths[i]));
	}
	std::string MaterialPaths[]
	{
	"Assets/Shader/Camera.shader",
	"Assets/Shader/Voronoi.shader"
	};

	Material* BaseMaterial = new Material(MaterialPaths[0]);
	Material* ComplexMaterial = new Material(MaterialPaths[1]);

	//todo: should remove this reference
	renderer->m_materials.push_back(BaseMaterial);
	renderer->m_materials.push_back(ComplexMaterial);

	renderer->AddRenderElement(Sprite(BaseMaterial, 3, "Plane 0"));
	renderer->AddRenderElement(Sprite(BaseMaterial, 0, "Plane 1"));
	renderer->AddRenderElement(Cube(BaseMaterial, 1, "Cube"));
	renderer->AddRenderElement(Cube(ComplexMaterial, 0, "Cube white"));
	//renderer->AddRenderElement(Line(BaseMaterial, vector2(0.0f, 0.0f), vector2(2.0f, 2.0f)));

	{
		/*
		For setting random position
		*/
		int distance = 4;
		for (int i = 0; i < renderer->GetRenderObjectCount(); i++)
		{
			vector3 randomPos = vector3(Mathf::Random(-distance, distance), Mathf::Random(-distance, distance), 0.0f);

			auto render = renderer->GetRenderobj(i);
			render->m_transform.position = randomPos;
		}
	}

	const auto& app = GB::Application::Get().GetWindow();
	float x = (float)app.GetWidth() / 2.0f;
	float y = (float)app.GetHeight() / 2.0f;
	GB::Cursor::SetCursorPosition(x, y);
	prevMouse = vector3(Input::GetMouseX() / x, Input::GetMouseY() / y, 0);

	GB::Camera::GetMain()->SetPosition(vector3(0.0f, 0.5f, 10.0f));
	GB::Camera::GetMain()->SetRotation(0, -90, 0);
}

void FreeCamera::OnUpdate()
{

	UpdateCameraMovement();
	Camera* camera = GB::Camera::GetMain();

	if (Input::IsKeyPressed(GB_KEY_W))
	{
		m_Direction = camera->GetPosition();
		m_Direction += camera->GetForward() * m_MovSpeed;
		camera->SetPosition(m_Direction);
	}
	else if (Input::IsKeyPressed(GB_KEY_S))
	{

		m_Direction = camera->GetPosition();
		m_Direction += camera->GetForward() * -m_MovSpeed;
		camera->SetPosition(m_Direction);
	}

	if (Input::IsKeyPressed(GB_KEY_A))
	{
		m_Direction = camera->GetPosition();
		m_Direction += glm::cross(camera->GetForward(), vector3(0, 1, 0)) * -m_MovSpeed;
		camera->SetPosition(m_Direction);
	}
	else if (Input::IsKeyPressed(GB_KEY_D))
	{

		m_Direction = camera->GetPosition();
		m_Direction += glm::cross(camera->GetForward(),vector3(0,1,0))* m_MovSpeed;
		camera->SetPosition(m_Direction);
	}
	GB_CLIENT_INFO("CDir {0}", camera->GetForward());
}

void FreeCamera::UpdateCameraMovement()
{
	timer += Time::DeltaTime();
	//	obj->m_transform.Lerp0(glm::vec3(0.0f, 0.0f, 0.0f), destiny, std::abs(std::sin(timer)));
	float x = Input::GetMouseX() / ((float)Application::Get().GetWindow().GetWidth() * 0.5f);
	float y = Input::GetMouseY() / ((float)Application::Get().GetWindow().GetHeight() * 0.5f);
	//obj->m_transform.Translate(glm::vec3((x, y, 0.0f)));
	vector3 mouse = vector3(x, y, 0);
	Camera* camera = Camera::GetMain();
	vector3 diff = (mouse - prevMouse) * m_CameraRotationSpeed;
	prevMouse = mouse;
	vector3 rotation = camera->GetRotation();
	camera->SetRotation((-diff.y) + rotation.x, diff.x + rotation.y, rotation.z);

}

void FreeCamera::OnImguiRender()
{
	editor.ImguiRender();
	static int rendermode = 4;
	static Texture2D* texture = nullptr;

	GB::Camera::GetMain()->ImguiEditor();
	ImGui::Begin("Profiling");
	if (ImGui::Button("OpenFile"))
	{
		std::string path;
		if (IO::GetPathDialogBox(path))
		{
			GB_CORE_TRACE("Ruta conseguida {0}", path.c_str());

			texture = Texture2D::Create(path);
		}

	}

	if (texture != nullptr)
	{

		ImGui::Image((ImTextureID)texture->GetID(), ImVec2(200, 200));
	}
	else
	{
		ImGui::Text("Time: %2f", timer);
	}
	ImGui::Text("Deltatime: %2f", Time::DeltaTime());
	ImGui::Text("FPS: %f", Time::GetMiliseconds());
	ImGui::SliderFloat("VelocityMove", &m_CameraRotationSpeed, 0.0f, 100.0f);

	ImGui::PlotLines("Time", [](void* data, int idx)
		{
			return idx * Time::DeltaTime();
		}, NULL, 100);

	static bool isvSync = Application::Get().GetWindow().IsVSync();
	if (ImGui::Button("VSync"))
	{
		isvSync = !isvSync;
		Application::Get().GetWindow().SetVSync(isvSync);
	}
	ImGui::SameLine();
	ImGui::Text(isvSync ? "true" : "false");

	ImGui::Text("Mouse %2f,%2f", CameraDirection().x, CameraDirection().y);
	ImGui::DragFloat("Camera distance", &distance);
	ImGui::DragFloat("CameraRot Speed", &m_CameraRotationSpeed, 0.01f);
	ImGui::DragFloat("CameraMove Speed", &m_MovSpeed, 0.01f);



	ImGui::End();


}

void FreeCamera::OnEvent(GB::Event& event)
{
	if (event.GetEventType() == GB::EventType::MouseScrolled)
	{

		GB::MouseScrolledEvent& e = (GB::MouseScrolledEvent&) event;
	}

}
