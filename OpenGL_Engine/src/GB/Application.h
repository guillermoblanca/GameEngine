#pragma once
#include "gbpch.h"
#include "Core.h"
#include "Window.h"
#include "GB\Events\Event.h"
#include "GB\Events\ApplicationEvent.h"
#include "LayerStack.h"

#include "ImGui\ImGuiLayer.h"
#include "GB\Render\Renderer.h"
#include "GameplayFramework\WorldManager.h"


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

		std::unique_ptr<Renderer>& GetRender() { return m_renderer; }
		std::unique_ptr<WorldManager>& GetWorld() { return m_worldManager; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;

		std::unique_ptr<ImGuiLayer> m_imguiLayer;
		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<WorldManager> m_worldManager;
		static Application* s_instance;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};
	
	 Application* CreateApplication();
}


