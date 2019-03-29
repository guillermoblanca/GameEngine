#pragma once
#include "gbpch.h"
#include "Core.h"
#include "Window.h"
#include "GB\Events\Event.h"
#include "GB\Events\ApplicationEvent.h"
#include "LayerStack.h"

#include "ImGui\ImGuiLayer.h"
#include "GB\Render\Renderer.h"
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

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;

		ImGuiLayer * m_imguiLayer;
		Renderer * m_renderer;

		static Application* s_instance;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};
	
	 Application* CreateApplication();
}


