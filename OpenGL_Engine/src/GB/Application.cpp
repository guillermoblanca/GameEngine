#include "gbpch.h"
#include "Application.h"
#include "GB\ImGui\ImGuiLayer.h"
#include "glad\glad.h"
#include "GB\Input.h"
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

	m_renderer = std::unique_ptr<Renderer>(new Renderer());
	PushLayer(m_renderer.get());
}

GB::Application::~Application()
{
}

void GB::Application::Run()
{
	while (m_Running)
	{
		m_Window->OnUpdate();

		for (Layer* layer : m_LayerStack)
			layer->OnUpdate();

		m_renderer->Begin();
		m_renderer->OnRender();

	

		m_imguiLayer->Begin();
		for (Layer* layer : m_LayerStack)
			layer->OnImguiRender();
		m_imguiLayer->End();


	}
}
void GB::Application::OnEvent(Event & e)
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

void GB::Application::PushLayer(Layer * layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void GB::Application::PopLayer(Layer * layer)
{
	m_LayerStack.PopLayer(layer);
	layer->OnDetach();
}

bool GB::Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}
