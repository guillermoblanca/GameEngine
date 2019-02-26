#pragma once
#include "gbpch.h"
#include "ImGuiLayer.h"
#include "imgui.h"
#include "Platform\OpenGL\ImGui\ImGuiOpenGLRenderer.h"
#include "GB\Application.h"
#include "GLFW\glfw3.h"
GB::ImGuiLayer::ImGuiLayer() : Layer ("ImGuiLayer")
{
}

GB::ImGuiLayer::~ImGuiLayer()
{
}

void GB::ImGuiLayer::OnAttach()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	ImGui_ImplOpenGL3_Init("#version 410");

}

void GB::ImGuiLayer::OnDetach()
{
}

void GB::ImGuiLayer::OnUpdate()
{
	
	ImGuiIO& io = ImGui::GetIO();
	Application& app = Application::Get();
	io.DisplaySize = ImVec2(app.GetWindow().GetWidth(),app.GetWindow().GetHeight());
	float time = (float)glfwGetTime();
	io.DeltaTime = m_time > 0 ? (time - m_time) : (1.0f / 60.0f);
	m_time = time;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	static bool show = true;

	ImGui::ShowDemoWindow(&show);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

