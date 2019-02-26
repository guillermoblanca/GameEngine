#pragma once
#include "gbpch.h"
#include "Window.h"
#include "Core.h"
#include "GB\Events\ApplicationEvent.h"
namespace GB
{
	 class GBAPI Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		inline static Application &Get() { return *s_instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		static Application* s_instance;
		bool m_Running = true;
	};
	
	 Application* CreateApplication();
}


