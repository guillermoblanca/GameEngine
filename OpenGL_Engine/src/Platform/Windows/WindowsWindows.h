#pragma once
#include "gbpch.h"
#include "GB\Window.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"
namespace GB
{
	class GBAPI WindowsWindows : public Window
	{
	public:
		WindowsWindows(const WindowsProps& props);
		virtual ~WindowsWindows();

		void OnUpdate() override;

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; }
		inline unsigned int GetWidth()  const { return m_data.width; }
		inline unsigned int GetHeight() const { return m_data.height; }

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		virtual void Init(const WindowsProps& props);
		virtual void ShutDown();
	private:
		GLFWwindow* m_window;

		struct WindowsData
		{
			std::string title;
			unsigned int width, height;
			bool vSync;
			EventCallbackFn EventCallback;
		};
		WindowsData m_data;
	};
}