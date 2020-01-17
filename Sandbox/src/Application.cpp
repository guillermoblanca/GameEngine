#include "GB.h"
#include "gbpch.h"
#include "Application.h"
#include "imgui\imgui.h"
#include "GB/ImportTools/IO.h"
#include "glm/gtc/type_ptr.hpp"

using namespace GB;

struct DATA
{
	float position;
	uint32_t ID;
	std::string name;
};
void LayerExample::OnAttach()
{

	//todo: optimize
	std::vector<Mesh*> meshs;

	Mesh debugMesh;
	MeshReader::ConvertFileToMesh("Assets/Mesh/sphere.obj", debugMesh);

	meshs.push_back(MeshReader::ReadMeshFromFile("Assets/Mesh/sphere.obj"));
	meshs.push_back(MeshReader::ReadMeshFromFile("Assets/Mesh/cubeonemeter.obj"));


	for (size_t i = 0; i < meshs.size(); i++)
	{
		GB::RenderObject* renderObject = new GB::RenderObject(Renderer::Get().GetMaterials()[0], meshs[i]->name);
		renderObject->Create(*meshs[i]);
		renderObject->m_textureID = 0;
		renderObject->m_transform.Translate({ i * 1.5f,0,0 });
		Renderer::Get().PushObj(renderObject);
	}


}
void LayerExample::OnUpdate()
	{
	//esto no es correcto porque se tiene que calcular la posicion con respecto a la camara
	//de screen coordinate a world coordinate
		if (Input::IsMousePressed(0))
		{
		auto mousePos = Input::GetMousePosition();
		mousePos.x /= (float)Application::Get().GetWindow().GetWidth();
		mousePos.y /= (float)Application::Get().GetWindow().GetHeight();
		for (size_t i = 0; i < Renderer::Get().GetRenderObjectCount(); i++)
		{
			auto renderer = Renderer::Get().GetRenderobj(i);
			bool objectIsSelected = CollisionManager::CheckCollision({ mousePos,0.5f,0.5f }, { renderer->m_transform.position,1,1 });
			if (objectIsSelected)
			{
				renderer->m_color = { 1.0f,0.0f,0.0f,1.0f };
				return;
			}
		}
	}
}
void LayerExample::OnImguiRender()
{

}

void LayerExample::OnEvent(GB::Event& event)
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
}

float velocity = 5.0f;
void FreeCamera::OnUpdate()
{

	timer += Time::DeltaTime();
	//	obj->m_transform.Lerp0(glm::vec3(0.0f, 0.0f, 0.0f), destiny, std::abs(std::sin(timer)));
	float x = Input::GetMouseX() / (float)Application::Get().GetWindow().GetWidth() * 16;
	float y = Input::GetMouseY() / (float)Application::Get().GetWindow().GetHeight() * 16;
	//obj->m_transform.Translate(glm::vec3((x, y, 0.0f)));
	Camera::GetMain()->CameraInput(velocity);
	if (GB::Input::IsMousePressed(1))
	{

		vector2 diff = CameraDirection();
		GB::Camera::GetMain()->Translate(glm::vec3(diff.x * velocity, -diff.y * velocity, 0.0f));
	}

	if (GB::Input::IsMousePressed(2))
	{
		float diff = CameraDirection().y;
		GB::Camera::GetMain()->Translate(glm::vec3(0.0f, 0.0f, diff * velocity * 2));

	}

	if (Input::IsKeyPressed(GB_KEY_LEFT_ALT) && Input::IsMousePressed(0))
	{
		vector2 position = CameraDirection();


		GB::Camera::GetMain()->Rotate(position.x, glm::vec3(0.f, 1.0f, 0.0f));
		GB::Camera::GetMain()->Rotate(position.y, glm::vec3(1.f, 0.0f, 0.0f));
	}

	/*
	Testing a error in the renderobjects queue
	*/


	unsigned int id = 1;
	RenderObject* obj = (RenderObject*)Renderer::Get().GetRenderobj(id);
	if (obj == nullptr)return;
	static int count = Renderer::Get().GetRenderObjectCount();
	RenderObject* obj1 = (RenderObject*)Renderer::Get().GetRenderobj(id + 1);

	float distObj = 2.0f;
	float t = timer;
	obj->m_transform.RotateAround(obj1->m_transform.position, distObj, timer);
	//obj1->m_transform.position = vector3(t, t* cos(t), t*sin(t));
	return;

	for (int i = 1; i < count; i++)
	{
		RenderObject* render = (RenderObject*)Renderer::Get().GetRenderobj(i);
		vector2 position = vector2(render->m_transform.position.x, render->m_transform.position.y);
		BoxCollider box = { position,1,1 };

		RenderObject* render1 = (RenderObject*)Renderer::Get().GetRenderobj(i - 1);
		vector2 position1 = vector2(render1->m_transform.position.x, render1->m_transform.position.y);
		BoxCollider box1 = { position1,1,1 };

		if (CollisionManager::CheckCollision(box1, box))
		{
			render->m_color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

			//GB_CORE_INFO("Obj {0}, Obj2 {1}", render->m_transform.position, render1->m_transform.position);
		}


	}

	if (Input::IsKeyPressed(GB_KEY_W))
	{
		obj->m_transform.position = obj->m_transform.position + (glm::vec3(0.f, velocity * Time::DeltaTime(), 0.0f));
	}
	else
		if (Input::IsKeyPressed(GB_KEY_D))
		{
			obj->m_transform.position = obj->m_transform.position + (glm::vec3(velocity * Time::DeltaTime(), 0.0f, 0.0f));
		}
	if (Input::IsKeyPressed(GB_KEY_A))
	{
		obj->m_transform.position = obj->m_transform.position + (glm::vec3(-velocity * Time::DeltaTime(), 0.0f, 0.0f));
	}
	else if (Input::IsKeyPressed(GB_KEY_S))
	{
		obj->m_transform.position = obj->m_transform.position + (glm::vec3(0.0f, -velocity * Time::DeltaTime(), 0.0f));
	}


}

void FreeCamera::OnImguiRender()
{
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
		RenderObject* obj = (RenderObject*)Renderer::Get().GetRenderobj(1);
		if (obj == nullptr)return;
		Camera::GetMain()->LookAt(obj->m_transform.position, distance);
	}
	ImGui::DragInt("RenderMode", &rendermode, 1, 0, (int)GB::Renderer::ERenderMode::Triangles);

	Renderer::Get().SetRenderMode(GB::Renderer::ERenderMode(rendermode));

	ImGui::End();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				DATA data = { 20,2,"Eva" };

				IO::WriteFile(data, "foo.gb");
			}
			if (ImGui::MenuItem("Open"))
			{
				DATA data = IO::ReadFile<DATA>("foo.gb");
				GB_CORE_TRACE("DATA: {0},{1},{2}", data.ID, data.position, data.name.c_str());
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

}

void FreeCamera::OnEvent(GB::Event& event)
{
	if (event.GetEventType() == GB::EventType::MouseScrolled)
	{

		GB::MouseScrolledEvent& e = (GB::MouseScrolledEvent&) event;
	}

}


#pragma endregion

#pragma region GameSystem

GameSystem* GameSystem::m_instance = new GameSystem();
#pragma endregion

void GameSystem::AddGameObject(Actor& gameObject)
{
	m_gameObjects.push_back(&gameObject);
}
