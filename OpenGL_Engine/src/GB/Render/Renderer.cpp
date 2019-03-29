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
		-0.5f,-0.5f,
		 0.5f,-0.5f,
		 0.5f, 0.5f,
		-0.5f, 0.5f,
	};
	unsigned int indices[]
	{
		0,1,2,
		2,3,0
	};
	

	VertexArray va;
	VertexBuffer vb(positions, 4 * 2 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	
	IndexBuffer ib(indices, 6);
	material.CreateShader("Assets/Shader/Complex.shader");
	

	//bind

//	va.Bind();
	//ib.Bind();
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
	static float x, y, z;
	static float size, tone;
	ImGui::Begin("Renderer editor");
	ImGui::Text("Time: %f",glfwGetTime());
	ImGui::Spacing();
	ImGui::SliderFloat("R", &r,0,255);
	ImGui::SliderFloat("G", &g,0,255);
	ImGui::SliderFloat("B", &b, 0, 255);
	ImGui::Spacing();
	ImGui::InputFloat("X", &x);
	ImGui::InputFloat("Y", &y);
	ImGui::InputFloat("Z", &z);
	ImGui::InputFloat("size",&size);
	ImGui::SliderFloat("tone",&tone, 0, 3);
	ImGui::End();
	
	Color color = Color(r == 0 ? 0 : r / 255, g == 0 ? 0 : g / 255, b == 0 ? 0 : b / 255);
//	material.GetParam().SetVector4("u_Color", color.r, color.g, color.b,color.a);
//	material.GetParam().SetFloat("u_time", glfwGetTime());
	auto glError = glGetError();
	if(glError != 0)GB_CORE_ERROR("GL ERROR: {0}", glError);

	float width = Application::Get().GetWindow().GetWidth();
	float height = Application::Get().GetWindow().GetHeight();
	material.GetParam().SetVector2("u_resolution",width , height);
	//material.GetParam().SetFloat("u_size", size);
	material.GetParam().SetFloat("u_tone", tone);
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
