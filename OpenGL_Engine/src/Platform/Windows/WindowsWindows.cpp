#pragma once
#include "gbpch.h"
#include "WindowsWindows.h"

#include "GB\Events\ApplicationEvent.h"
#include "GB\Events\MouseEvent.h"
#include "GB\Events\KeyEvent.h"
#include "Platform\OpenGL\OpenGLGraphicContext.h"
#include "glad\glad.h"
namespace GB
{
	static bool s_GLFWInitialized = false;
	static void GLFWErrorCallback(int error, const char* description)
	{
		GB_CORE_ERROR("GLFW Error: {0}: {1}", error, description);
	}
	Window* Window::Create(const WindowsProps& props)
	{
		return new WindowsWindows(props);
	}

	WindowsWindows::WindowsWindows(const WindowsProps& props)
	{
		Init(props);
	}
	WindowsWindows::~WindowsWindows()
	{
		ShutDown();
	}
	void WindowsWindows::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}
	void WindowsWindows::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_data.vSync = enabled;
	}
	bool WindowsWindows::IsVSync() const
	{
		return m_data.vSync;
	}

	void WindowsWindows::Init(const WindowsProps& props)
	{
		m_data.title = props.Title;
		m_data.height = props.Height;
		m_data.width = props.Width;


		if (!s_GLFWInitialized)
		{
			int succes = glfwInit();
			GB_CORE_ASSERT("GLFW Failed: {0}", succes);
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;

		}

		m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);


		m_Context = new OpenGLGraphicContext(m_window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_window, &m_data); //todo: research
		SetVSync(true);

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
				WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);

				glViewport(0, 0, width, height);
			});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scanCode, int action, int mods)
			{
				WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

				switch (action) {
					{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
					}
				}
			});

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});


	}
	void WindowsWindows::ShutDown()
	{
		glfwDestroyWindow(m_window);
	}
}