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
void GB::Renderer::OnAttach()
{
	GB_CORE_INFO("Initialized Render class");

	//facilita poner el modo para alfas debo crear algo para que permita iterar entre un sistema y otro
	unsigned int indices[]
	{
		0,1,2,
		2,3,0
	};
	material.CreateShader("Assets/Shader/Texture.shader");
	m_renderObject = new RenderObject(indices, 6, &material);
	texture = new Texture("Assets/Texture/lion-logo.png");
	texture1 = new Texture("Assets/Texture/Game.png");
	m_renderObject->SetRenderMode(ERenderMode::BLEND);


	material1.CreateShader("Assets/Shader/Uniform.shader");
	m_renderObject1 = new RenderObject(indices, 6, &material1);

}
void GB::Renderer::OnDetach()
{
	delete texture;
	delete texture1;
	delete m_renderObject;
	delete m_renderObject1;
}

void GB::Renderer::OnRender()
{
	m_renderObject1->Render();
	m_renderObject->Render();
}

void GB::Renderer::OnImguiRender()
{
	static float color[4] = { 1,1,1,1 };
	static float s_color[4] = { 255,255,255,255 };
	static float position[2];
	static int changeTex = 0;
	static float scale[3] = { 1,1,1 };
	static float rotator = 0;

	static bool show_new = false;
	static bool show_open = false;
	static bool show_save = false;
	static bool show_objpro = false;
	//for menu test


	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("New", NULL, &show_new);
			ImGui::MenuItem("Open", NULL, &show_open);
			ImGui::MenuItem("Save", NULL, &show_save);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Render editor"))
		{
			ImGui::MenuItem("RenderObject properties", NULL, &show_objpro);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	if (show_objpro) RenderEditorObj(position, scale, &rotator, &changeTex, color);

	ImGui::Begin("Render object properties 1");
	ImGui::SliderFloat4("Col", s_color, 0.0f, 255, "%.0f");
	ImGui::End();

	float width = (float)Application::Get().GetWindow().GetWidth();
	float height = (float)Application::Get().GetWindow().GetHeight();




	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(position[0] / width, position[1] / height, 0.0f));
	trans = glm::rotate(trans, rotator, glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::scale(trans, glm::vec3(scale[0], scale[1], scale[2]));

	if (changeTex == 1)
	{
		texture1->Bind(1);

	}
	else
	{
		texture->Bind(0);
	}

	static auto mat = m_renderObject->GetMat();
	mat->Bind();
	mat->SetVector4("u_Color", color[0], color[1], color[2], color[3]);
	mat->SetMat4("u_transform", trans);
	mat->SetInt("u_Texture", changeTex);

	static auto mat1 = m_renderObject1->GetMat();
	mat1->Bind();
	mat1->SetVector4("u_Color", s_color[0] / 255, s_color[1] / 255, s_color[2] / 255, s_color[3] / 255);
}

void GB::Renderer::Begin()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0.5f, 0.5f, 1);
}

void GB::Renderer::End()
{
	//todo fix breaks imgui
	auto window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
	glfwSwapBuffers(window);
}

void GB::Renderer::RenderEditorObj(float *position, float *scale, float *rotator, int *changeTex, float *color)
{

	static bool RotState = false;
	static bool show_transform = true;
	ImGuiDir dir_transform = show_transform ? ImGuiDir_Down : ImGuiDir_Right;

	static bool show_texinfo = true;
	ImGuiDir dir_texinfo = show_texinfo ? ImGuiDir_Down : ImGuiDir_Right;
	static ImVec4 colorformat = ImColor(color[0], color[1], color[2], color[3]);

	ImGui::Begin("Renderer editor");

	ImGui::Text("Time: %f", glfwGetTime());
	ImGui::Spacing();

	if (ImGui::Button("Rotate")) RotState = !RotState;

	ImGui::SliderInt("change texture", changeTex, 0, 1);

	if(ImGui::ArrowButton("transform_button", dir_transform)) show_transform = !show_transform;
	ImGui::SameLine();
	ImGui::Text("Transform");
	if (show_transform)
	{
		ImGui::DragFloat2("Pos:", position);
		ImGui::DragFloat3("Scale:", scale, 0.1f);
		ImGui::DragFloat("rot", rotator, 0.1f);
	}
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::ColorPicker4("##picker", (float*)&colorformat, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);

	ImGui::Separator();

	if (ImGui::ArrowButton("texinfo_button", dir_transform)) { show_texinfo = !show_texinfo; }
	ImGui::SameLine();
	ImGui::Text("Texture info");
	if (show_texinfo)
	{
		ImGui::Text("Lion Texture");
		ImGui::Text("Path %s", texture->GetPath().c_str());
		ImGui::Text("Width %d", texture->GetWidth());
		ImGui::Text("Height %d", texture->GetHeight());
		ImGui::Text("BPP %d", texture->GetBPP());

		ImGui::Spacing();
		ImGui::Separator();

		ImGui::Text("Game Texture");

		ImGui::Text("Path %s", texture1->GetPath().c_str());
		ImGui::Text("Width %d", texture1->GetWidth());
		ImGui::Text("Height %d", texture1->GetHeight());
		ImGui::Text("BPP %d", texture1->GetBPP());
	}
	ImGui::End();

	color[0] = colorformat.x;
	color[1] = colorformat.y;
	color[2] = colorformat.z;
	color[3] = colorformat.w;
	if (RotState) *rotator = (float)glfwGetTime();
}
