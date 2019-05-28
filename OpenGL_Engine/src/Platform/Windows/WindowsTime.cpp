#include "gbpch.h"
#include "WindowsTime.h"
#include "GLFW\glfw3.h"
namespace GB
{
	Time* WindowsTime::s_instance = new WindowsTime();
	float WindowsTime::m_deltaTime = 0;

	float WindowsTime::Impl_DeltaTime()
	{
		float r = (float)glfwGetTime() - m_deltaTime;
		m_deltaTime = (float)glfwGetTime();
		return r;
	}

	float WindowsTime::ImplGetTime()
	{
		return (float)glfwGetTime();
	}
}
