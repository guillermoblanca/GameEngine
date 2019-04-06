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
	m_renderObject = new RenderObject(indices, 6);
	m_renderObject->SetRenderMode(ERenderMode::BLEND);
	material.CreateShader("Assets/Shader/Texture.shader");
	material.Bind();

	texture = new Texture("Assets/Texture/Game.png");

	texture->Bind(0);

	material.GetParam().SetInt("u_Texture", 0);

}
void GB::Renderer::OnDetach()
{
	delete texture;
}

void GB::Renderer::OnRender()
{
	m_renderObject->Bind();
	m_renderObject->Render();
	m_renderObject->UnBind();
}

void GB::Renderer::OnImguiRender()
{
	static float r = 255, g, b, a;

	static float position[4];
	static bool RotState = 0;
	static float scale[3] = { 1,1,1 };
	static float rotator = 0;
	ImGui::Begin("Renderer editor");

	ImGui::Text("Time: %f", glfwGetTime());
	ImGui::Spacing();
	ImGui::SliderFloat("R", &r, 0, 255);
	ImGui::SliderFloat("G", &g, 0, 255);
	ImGui::SliderFloat("B", &b, 0, 255);

	ImGui::Text("Path %s", texture->GetPath().c_str());
	ImGui::Text("Width %d",texture->GetWidth());
	ImGui::Text("Height %d", texture->GetHeight());
	ImGui::Text("BPP %d",texture->GetBPP());
	if(ImGui::Button("Rotate")) RotState = !RotState;
	ImGui::DragFloat2("Pos:", position);
	ImGui::DragFloat3("Scale:", scale,0.1f);
	if (RotState)
	{
		rotator = (float)glfwGetTime();
	}
	else
	{
		ImGui::DragFloat("rot", &rotator,0.1f);
	}
	ImGui::End();
	Color color = Color(r == 0 ? 0 : r / 255, g == 0 ? 0 : g / 255, b == 0 ? 0 : b / 255);

	float width = (float)Application::Get().GetWindow().GetWidth();
	float height = (float)Application::Get().GetWindow().GetHeight();


	material.GetParam().SetVector4("u_Color", r/255.0f,g/255.0f,b/255.0f,1);
	
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(position[0]/width, position[1]/height, 0.0f));
	trans = glm::rotate(trans, rotator, glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::scale(trans, glm::vec3(scale[0],scale[1],scale[2]));
	material.GetParam().SetMat4("u_transform", trans);
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
