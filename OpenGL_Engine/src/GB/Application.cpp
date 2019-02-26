#include "gbpch.h"
#include "Application.h"
#include "GB\Render\Render.h"
#include "GB\ImGui\ImGuiLayer.h"
namespace GB
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_instance = nullptr; 
}
GB::Application::Application()
{
	s_instance = this;
	m_Window = std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	//init window
	GB_CORE_INFO("Initialized Core application");
}

GB::Application::~Application()
{
	
}

void GB::Application::Run()
{
	Render render;
	render.Init();
	while (m_Running)
	{
		render.Draw();
		m_Window->OnUpdate();
	}
}

void GB::Application::OnEvent(Event & e)
{
	GB_CORE_INFO(e.ToString());
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

}

bool GB::Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}
