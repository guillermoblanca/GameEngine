#include "gbpch.h"
#include "WindowsTime.h"
#include "GLFW\glfw3.h"

namespace GB
{
	Time* WindowsTime::s_instance = new WindowsTime();
	float WindowsTime::m_deltaTime = 0;
	float WindowsTime::m_lastTime = 0;
	float WindowsTime::Impl_DeltaTime()
	{
		m_deltaTime = glfwGetTime() - m_lastTime;
		m_lastTime= glfwGetTime();
		return m_deltaTime;
	}

	float WindowsTime::ImplGetTime()
	{
		return (float)glfwGetTime();
	}
	float WindowsTime::ImplGetMiliseconds()
	{
    return m_deltaTime * 1000.0f;
	}
}
