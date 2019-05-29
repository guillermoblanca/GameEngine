#include "gbpch.h"
#include "Renderer.h"


#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "GB\Application.h"
#include "imgui.h"
#include "GB\Math.h"
#include "GB/Input.h"
#include "Camera.h"

namespace GB
{
	Renderer* Renderer::m_singleton = nullptr;


	Renderer::Renderer(): m_renderIndex(0)
	{
		m_singleton = this;
	}

	Renderer::~Renderer()
	{
		for (IRender* irender : m_renderObjects)
		{
			delete irender;
		}

		for (Material* mat : m_materials)
		{
			delete mat;
		}
	}

	void Renderer::OnAttach()
	{
		GB_CORE_INFO("Initialized Render class");

		//facilita poner el modo para alfas debo crear algo para que permita iterar entre un sistema y otro
		const float vertices[] = {
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,//0
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,//1
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,//2
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,//3

	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,//4
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,//5
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,//6
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,//7

	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,//8
	   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,//9
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,//10

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,//11
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,//12
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,//13

		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,//14

	   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,//15
		};

		unsigned int indiceCube[]
		{
		0,1,2,2,3,0,
		4,5,6,6,7,4,
		8,9,10,10,4,8,
		11,2,12,12,13,11,
		10,14,5,5,4,10,
		3,2,11,11,15,3
		};
		const float positions[]
		{//vertices           //uv
			-0.5f,-0.5f,0.0f, 0.0f, 0.0f,
			 0.5f,-0.5f,0.0f, 1.0f, 0.0f,
			 0.5f, 0.5f,0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f,0.0f, 0.0f, 1.0f
		};

		unsigned int indices[]
		{
			0,1,2,
			2,3,0
		};

		AlphaRender(true);
		glEnable(GL_DEPTH_TEST);
		PushObj((IRender*)new RenderObject());
		PushObj((IRender*)new RenderObject());
		m_textures.push_back(new Texture("Assets/Texture/Game.png", 0));
		m_textures.push_back(new Texture("Assets/Texture/Brick.png", 1));
		m_materials.push_back(new Material("Assets/Shader/Camera.shader"));

		RenderObject* render =(RenderObject*) m_renderObjects[0];
		render->Create(positions, 5 * 4 * sizeof(float), indices, 6);
		render = (RenderObject*) m_renderObjects[1];
		render->Create(vertices, 5 * 16 * sizeof(float), indiceCube, 36);
	}
	void Renderer::OnDetach()
	{
		for (int i = 0; i < m_textures.size(); i++) delete m_textures[i];
		for (int i = 0; i < m_renderObjects.size(); i++) delete m_renderObjects[i];
	}

	void Renderer::OnRender()
	{
		Begin();
		for (int i = 0; i < m_renderObjects.size(); i++)
		{
			auto obj = (RenderObject*)m_renderObjects[i];
			m_textures[i]->Bind(0);
			obj->Render(*m_materials[0],(int)this->mode);
		}
	}


	void Renderer::Begin()
	{
		glClearColor(0, 0.5f, 0.5f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::End()
	{
		static auto window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		glfwSwapBuffers(window);
	}
	void Renderer::PushObj(IRender * obj)
	{
		m_renderObjects.emplace(m_renderObjects.begin() + m_renderIndex, obj);
		m_renderIndex++;
	}
	void Renderer::PushOverLay(IRender * obj)
	{
		m_renderObjects.emplace_back(obj);
	}
	void Renderer::PopObj(IRender * obj)
	{
		auto it = std::find(m_renderObjects.begin(), m_renderObjects.end(), obj);
		if (it != m_renderObjects.end())
		{
			m_renderObjects.erase(it);
			m_renderIndex--;
		}
	}
	void Renderer::PopOverlay(IRender * obj)
	{
		auto it = std::find(m_renderObjects.begin(), m_renderObjects.end(), obj);
		if (it != m_renderObjects.end())
			m_renderObjects.erase(it);
	}
	void Renderer::SetRenderMode(RenderMode mode)
	{
		this->mode = mode;
	}
	void Renderer::OnImguiRender()
	{
		ImGui::Begin("Render");

		static int i = 0;
		static float rot[] = { 0,0,0 };
		glm::vec3 position;
		glm::quat quat;
		glm::vec3 scale;
		glm::vec3 skew;
		glm::vec4 perspective;
		RenderObject* render = (RenderObject*) m_renderObjects[i];
		glm::decompose(render->m_transform.GetMat4(), scale, quat, position, skew, perspective);

		glm::vec3 rotator = render->m_transform.rotation;
		ImGui::DragInt("INDEX", &i, 1.0f, 0, m_renderObjects.size() - 1);

		ImGui::DragFloat3("Position", (float*)&position, 0.1f);
		ImGui::DragFloat3("Rotation", rot, 0.1f);
		ImGui::ColorPicker4("Color", (float*)&render->m_color);
		ImGui::Text("Pos: %2f,%2f,%2f",position.x,position.y,position.z);
		ImGui::Text("Rotation: %2f,%2f,%2f",Math::ToDegrees(rotator.x),Math::ToDegrees(rotator.y),Math::ToDegrees(rotator.z));
		ImGui::Text("Scale: %2f,%2f,%2f",scale.x,scale.y,scale.z);

		ImGui::End();
		
		render->m_transform.Translate(position);
		render->m_transform.Rotate(glm::vec3(glm::radians(rot[0]), glm::radians(rot[1]), glm::radians(rot[2])));

	}
	void Renderer::AlphaRender(bool active)
	{
		if (active)
		{

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else
		{
			glDisable(GL_BLEND);
		}
	}
}