#include "gbpch.h"
#include "OpenGLGraphicContext.h"
#include <GLFW\glfw3.h>
#include <glad\glad.h>
namespace GB
{
	OpenGLGraphicContext::OpenGLGraphicContext(GLFWwindow* windowHandle): m_WindowHandle(windowHandle)
	{
		GB_CORE_ASSERT(windowHandle, "Window handle is null");
		GB_CORE_INFO("OpenGL Context created");

	}
	void OpenGLGraphicContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GB_CORE_ASSERT(status, "Failed to initialize GLAD");
		GB_CORE_INFO("Renderer: {0}",glGetString(GL_RENDERER));
		GB_CORE_INFO("Version: {0}",glGetString(GL_VERSION));
		GB_CORE_INFO("Version Shader: {0}",glGetString(GL_SHADING_LANGUAGE_VERSION));

	}
	void OpenGLGraphicContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);

	}

}