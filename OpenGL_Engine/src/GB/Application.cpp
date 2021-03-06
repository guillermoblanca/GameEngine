#include "gbpch.h"
#include "Application.h"
#include "GB\ImGui\ImGuiLayer.h"
#include "GB\Input.h"
#include "GB/Render/RenderCommand.h"
#include "GB/Render/Camera.h"
#include "GLFW\glfw3.h"

namespace GB
{
	Application* Application::s_instance = nullptr;
}
GB::Application::Application()
{
	s_instance = this;
	m_Window = std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	//init window
	GB_CORE_INFO("Initialized Core application");

	m_imguiLayer = std::unique_ptr<ImGuiLayer>(new ImGuiLayer());
	PushLayer(m_imguiLayer.get());
	m_worldManager = std::make_unique<WorldManager>();
	PushLayer(m_worldManager.get());

	m_renderer = std::unique_ptr<Renderer>(new Renderer());
	m_renderer->Init();


}

GB::Application::~Application()
{
}

void GB::Application::Run()
{
	while (m_Running)
	{
		float time = (float)glfwGetTime();
		TimeStep timeStep = time - m_LastFrameTime;
		m_LastFrameTime = time;


		m_Window->OnUpdate();

		for (Layer* layer : m_LayerStack)
			layer->OnUpdate(timeStep);

		RenderCommand::Clear();
		Renderer::BeginScene(*Camera::GetMain());
		m_renderer->OnRender();
		Renderer::EndScene();


		m_imguiLayer->Begin();
		for (Layer* layer : m_LayerStack)
			layer->OnImguiRender();

		m_renderer->OnImguiRender();
		m_imguiLayer->End();

	}
}
void GB::Application::OnEvent(Event& e)
{
	//	GB_CORE_INFO(e.ToString());
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
	{
		(*--it)->OnEvent(e);
		if (e.Handled)
			break;
	}
}

void GB::Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void GB::Application::PopLayer(Layer* layer)
{
	m_LayerStack.PopLayer(layer);
	layer->OnDetach();
}

bool GB::Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}
