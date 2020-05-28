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

	GB::Camera::GetMain()->Translate(vector3(0.0f, 0.5f, -10.0f));
}

void FreeCamera::OnUpdate()
{

	UpdateCameraMovement();

	/*
	Testing a error in the renderobjects queue
	*/
	auto& render = Application::Get().GetRender();
	return;
	unsigned int id = 1;
	RenderObject* obj = (RenderObject*)render->GetRenderobj(id);
	if (obj == nullptr)return;
	static int count =  render->GetRenderObjectCount();
	RenderObject* obj1 = (RenderObject*)render->GetRenderobj(id + 1);

	float distObj = 2.0f;
	float t = timer;
	obj->m_transform.RotateAround(obj1->m_transform.position, distObj, timer);

}

void FreeCamera::UpdateCameraMovement()
{
	timer += Time::DeltaTime();
	//	obj->m_transform.Lerp0(glm::vec3(0.0f, 0.0f, 0.0f), destiny, std::abs(std::sin(timer)));
	float x = Input::GetMouseX() / (float)Application::Get().GetWindow().GetWidth();
	float y = Input::GetMouseY() / (float)Application::Get().GetWindow().GetHeight();
	//obj->m_transform.Translate(glm::vec3((x, y, 0.0f)));
	vector3 mouse = vector3(x, y,0);
	Camera* camera = Camera::GetMain();
	mouse *= velocity;
	camera->LookAt(vector3(x,-y,0),distance);

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
		ImGui::Image((ImTextureID)texture->GetID(), ImVec2(200, 200)); else

		ImGui::Text("Time: %2f", timer);
	ImGui::Text("Deltatime: %2f", Time::DeltaTime());
	ImGui::Text("FPS: %f", Time::GetMiliseconds());
	ImGui::SliderFloat("VelocityMove", &velocity, 0.0f, 100.0f);
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
	ImGui::DragFloat("Velocity", &velocity, 0.01f);
	ImGui::DragFloat3("Destiny", (float*)&destiny);

	if (ImGui::Button("LookAt"))
	{
		/*
		Todo: fix issue when there is no object
		*/
		RenderObject* obj = (RenderObject*)Application::Get().GetRender()->GetRenderobj(1);
		if (obj)
		{

		Camera::GetMain()->LookAt(obj->m_transform.position, distance);
		}
	}

	ImGui::End();


}

void FreeCamera::OnEvent(GB::Event& event)
{
	if (event.GetEventType() == GB::EventType::MouseScrolled)
	{

		GB::MouseScrolledEvent& e = (GB::MouseScrolledEvent&) event;
	}

}
