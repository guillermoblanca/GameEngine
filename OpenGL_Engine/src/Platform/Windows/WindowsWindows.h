#pragma once
#include "gbpch.h"
#include "GB\Window.h"
#include "GB\Render\GraphicContext.h"
#include "GLFW\glfw3.h"
namespace GB
{
	class WindowsInput;
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
		inline virtual void* GetNativeWindow()const { return m_window; }
	private:
		virtual void Init(const WindowsProps& props);
		virtual void ShutDown();
	private:
		GLFWwindow* m_window;
		GraphicContext* m_Context;
		struct WindowsData
		{
			std::string title;
			unsigned int width, height;
			bool vSync;
			EventCallbackFn EventCallback;
		};
		WindowsData m_data;
		
		friend WindowsInput;
	};
}