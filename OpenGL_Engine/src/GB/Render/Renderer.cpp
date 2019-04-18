#include "gbpch.h"
#include "Renderer.h"


#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "GB\Application.h"
#include "imgui.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "GB/Input.h"
#include "Camera.h"
namespace GB
{


	void Renderer::OnAttach()
	{
		GB_CORE_INFO("Initialized Render class");

		//facilita poner el modo para alfas debo crear algo para que permita iterar entre un sistema y otro

		const float positions[]
		{
			-0.5f,-0.5f, 0.0f, 0.0f,
			 0.5f,-0.5f, 1.0f, 0.0f,
			 0.5f, 0.5f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 1.0f
		};

		unsigned int indices[]
		{
			0,1,2,
			2,3,0
		};

		AlphaRender(true);

		m_renderObjects.push_back(new RenderObject(positions, 4 * 4 * sizeof(float), indices, 6, new Material("Assets/Shader/Texture.shader"), nullptr));
		m_renderObjects.push_back(new RenderObject(positions, 4 * 4 * sizeof(float), indices, 6, new Material("Assets/Shader/Texture.shader"), nullptr));
		m_textures.push_back(new Texture("Assets/Texture/Game.png",0));
		m_textures.push_back(new Texture("Assets/Texture/lion-logo.png",1));
		

	}
	void Renderer::OnDetach()
	{
		for (int i = 0; i < m_textures.size(); i++) delete m_textures[i];
		for (int i = 0; i < m_renderObjects.size(); i++) delete m_renderObjects[i];
	}

	void Renderer::OnRender()
	{
		static float width = (float)Application::Get().GetWindow().GetWidth();
		static float height = (float)Application::Get().GetWindow().GetHeight();
		glm::mat4 transform = glm::mat4(1.0f);

		for (int i = 0; i < m_renderObjects.size(); i++)
		{
			transform = glm::translate(transform, glm::vec3((i*500)/width, (float)i / height, 0.0f));
			transform = glm::scale(transform, glm::vec3(1.0f / (i + 1), 1.0f / (i + 1), 1.0f));

			auto obj = m_renderObjects[i];
			m_textures[i]->Bind(0);
			obj->GetMat()->Bind();
			obj->GetMat()->SetInt("u_Texture", 0);
			obj->GetMat()->SetMat4("u_transform", transform);
			obj->GetMat()->SetVector4("u_Color", 1.0f, 1.f,1.0f, 1.0f);
			obj->Render();
		}
	}

	void Renderer::OnImguiRender()
	{
		static float color[4] = { 1,1,1,1 };
		static float position[2];
		static int changeTex = 1;
		int changeTex1 = 1;
		static float scale[3] = { 1,1,1 };
		static float rotator = 0;
		static bool show_new = false;
		static bool show_open = false;
		static bool show_save = false;
		static bool show_quit = false;
		static bool show_objpro = true;
		static bool show_objpro1 = false;
		static bool show_shadercomp = false;
		static bool move_mouse = false;
		static bool move_mouse1 = false;
		static float color1[4] = { 1,1,1,1 };
		static float position1[2];
		static float rotator1 = 0;
		//for menu test


		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::MenuItem("New", NULL, &show_new);
				ImGui::MenuItem("Open", NULL, &show_open);
				ImGui::MenuItem("Save", NULL, &show_save);
				ImGui::MenuItem("Quit", NULL, &show_quit);
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Render editor"))
			{
				ImGui::MenuItem("RenderObject properties", NULL, &show_objpro);
				ImGui::MenuItem("RenderObject properties 1", NULL, &show_objpro1);
				ImGui::MenuItem("Shader compiler", NULL, &show_shadercomp);
				ImGui::EndMenu();
			}

			if (ImGui::Button("Compile shader"))
			{
				//m_renderObject->GetMat()->CreateShader("Assets/Shader/Camera.shader");

			}
			ImGui::EndMainMenuBar();
		}

		if (show_objpro) RenderEditorObj(position, scale, &rotator, &changeTex, color, &move_mouse);
		if (show_objpro1) RenderEditorObj(position1, scale, &rotator1, &changeTex1, color1, &move_mouse);
		//if (show_shadercomp) MaterialEditor(m_renderObject, *pathbuff);

		float width = (float)Application::Get().GetWindow().GetWidth();
		float height = (float)Application::Get().GetWindow().GetHeight();




		glm::mat4 trans = glm::mat4(1.0f);
		if (move_mouse)
		{
			float x = (float)Input::GetMouseX() / width;
			float y = -(float)Input::GetMouseY() / height;
			GB_CORE_TRACE("Mouse value {0}:{1}", x, y);
			trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
		}
		else
		{
			trans = glm::translate(trans, glm::vec3(position[0] / width, position[1] / height, 0.0f));
		}
		trans = glm::rotate(trans, rotator, glm::vec3(1.0f, 0.0f, 0.0f));
		trans = glm::scale(trans, glm::vec3(scale[0], scale[1], scale[2]));


		CameraEditor();
	}

	void Renderer::Begin()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0.5f, 0.5f, 1);
	}

	void Renderer::End()
	{
		//todo fix breaks imgui
		auto window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		glfwSwapBuffers(window);
	}

	void Renderer::RenderEditorObj(float *position, float *scale, float *rotator, int *changeTex, float *color, bool * move_mouse)
	{

		static bool RotState = false;
		bool show_transform = true;
		bool show_color = true;
		ImGuiDir dir_transform = show_transform ? ImGuiDir_Down : ImGuiDir_Right;

		static bool show_texinfo = true;
		ImGuiDir dir_texinfo = show_texinfo ? ImGuiDir_Down : ImGuiDir_Right;
		static ImVec4 colorformat = ImColor(color[0], color[1], color[2], color[3]);

		ImGui::Begin("Renderer editor");

		ImGui::Text("Time: %f", glfwGetTime());
		ImGui::Spacing();

		if (ImGui::Button("Rotate")) RotState = !RotState;
		if (ImGui::Button("Move with mouse")) *move_mouse = !*move_mouse;
		ImGui::SliderInt("change texture", changeTex, 0, 1);

		if (ImGui::CollapsingHeader("Transform", &show_transform))
		{
			ImGui::DragFloat2("Pos:", position);
			ImGui::DragFloat3("Scale:", scale, 0.1f);
			ImGui::DragFloat("rot", rotator, 0.1f);
		}
		ImGui::Spacing();
		ImGui::Spacing();
		if (ImGui::CollapsingHeader("Color editor", &show_color))
			ImGui::ColorPicker4("##picker", (float*)&colorformat, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);

		ImGui::Separator();

		if (ImGui::CollapsingHeader("Show texture info", &show_texinfo))
		{
			/*	auto texture = m_renderObject->GetMat()->GetTexture(0);
				ImGui::Text("Lion Texture");
				ImGui::Text("Path %s", texture->GetPath().c_str());
				ImGui::Text("Width %d", texture->GetWidth());
				ImGui::Text("Height %d", texture->GetHeight());
				ImGui::Text("BPP %d", texture->GetBPP());

				ImGui::Spacing();
				ImGui::Separator();

				ImGui::Text("Game Texture");
				auto texture1 = m_renderObject->GetMat()->GetTexture(1);
				ImGui::Text("Path %s", texture1->GetPath().c_str());
				ImGui::Text("Width %d", texture1->GetWidth());
				ImGui::Text("Height %d", texture1->GetHeight());
				ImGui::Text("BPP %d", texture1->GetBPP());*/
		}
		ImGui::End();

		color[0] = colorformat.x;
		color[1] = colorformat.y;
		color[2] = colorformat.z;
		color[3] = colorformat.w;
		if (RotState) *rotator = (float)glfwGetTime();
	}


	void Renderer::CameraEditor()
	{

		static float width = (float)Application::Get().GetWindow().GetWidth();
		static float height = (float)Application::Get().GetWindow().GetHeight();

		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		static float FOV = 45.0f;
		static float m_position[3] = { 0,0,-3 };
		static float m_rotation[3] = { 0,0,0 };
		static float m_rot = -55.0f;
		ImGui::Begin("Render object");

		ImGui::DragFloat3("Position", m_position, 0.1f);
		ImGui::DragFloat("Rotation", &m_rot, 0.1f);
		ImGui::End();

		model = glm::translate(model, glm::vec3(m_position[0], m_position[1], m_position[2]));
		model = glm::rotate(model, glm::radians(m_rot), glm::vec3(1.0f, 0.0f, 0.0f));

		Camera::ImguiEditor();

		glm::mat4 result = Camera::GetProj() * Camera::GetView() * model;
		/*	static auto mat = m_renderObject->GetMat();
			mat->Bind();
			mat->SetMat4("u_view", result);
	*/

	}

	void Renderer::MaterialEditor(RenderObject* renobj, char* pathbuff)
	{
		//todo: fix imgui::inputtext
		if (ImGui::BeginMenu("Render Obj"))
		{
			//ImGui::InputText("Path", pathbuff, 1024);

			if (ImGui::Button("Compile shader")) renobj->GetMat()->CreateShader(pathbuff);
			ImGui::EndMenu();
		}
	}
	void Renderer::AlphaRender(bool active)
	{
		if(active)
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