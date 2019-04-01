#include "gbpch.h"
#include "Renderer.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"


#include "VertexArray.h"
#include "IndexBuffer.h"

#include "GB\Application.h"
#include "imgui.h"

void GB::Renderer::OnAttach()
{
	GB_CORE_INFO("Initialized Render class");

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	
	IndexBuffer ib(indices, 6);
	material.CreateShader("Assets/Shader/Basic.shader");
	material.Bind();

	texture = new Texture("Assets/Texture/Game.png");

	texture->Bind(0); 
	
	material.GetParam().SetInt("u_Texture", 0);
}
void GB::Renderer::OnDetach()
{
	delete texture;
}
//todo: pasar a eventcallback y quitarlo
void GlClearError()
{
	while (GLenum GL_Error = glGetError())
	{
		GB_CORE_ERROR("GL ERROR {0}", GL_Error);
	}
}
void GB::Renderer::OnRender() 
{
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void GB::Renderer::OnImguiRender()
{
	static float r =255, g, b,a;


	ImGui::Begin("Renderer editor");

	ImGui::Text("Time: %f",glfwGetTime());
	ImGui::Spacing();
	ImGui::SliderFloat("R", &r,0,255);
	ImGui::SliderFloat("G", &g,0,255);
	ImGui::SliderFloat("B", &b, 0, 255);

	ImGui::Text("Path %s", texture->GetPath().c_str());
	ImGui::Text("Width %d",texture->GetWidth());
	ImGui::Text("Height %d", texture->GetHeight());
	ImGui::Text("BPP %d",texture->GetBPP());
	ImGui::End();
	Color color = Color(r == 0 ? 0 : r / 255, g == 0 ? 0 : g / 255, b == 0 ? 0 : b / 255);

	float width = (float)Application::Get().GetWindow().GetWidth();
	float height = (float)Application::Get().GetWindow().GetHeight();


}

void GB::Renderer::Begin()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0.5f, 0.5f, 1);
}

void GB::Renderer::End()
{
	//todo fix breaks imgui
	auto window = (GLFWwindow*) Application::Get().GetWindow().GetNativeWindow();
	glfwSwapBuffers(window);
}
