#include "gbpch.h"
#include "WindowsTime.h"
#include "GLFW\glfw3.h"

namespace GB
{
	Time* WindowsTime::s_instance = new WindowsTime();
	double WindowsTime::m_deltaTime = 0;
	double WindowsTime::m_lastTime = 0;
	double WindowsTime::m_unscaledDeltaTime = 0;

	long double WindowsTime::m_time = 0;

	float WindowsTime::m_timeScale = 1.0f;

	double WindowsTime::Impl_DeltaTime()
	{
		double tick = glfwGetTime();
		m_unscaledDeltaTime = tick - m_lastTime;
		m_lastTime = tick;
		m_deltaTime = m_unscaledDeltaTime * m_timeScale;
		return m_deltaTime;
	}

	double WindowsTime::ImplGetTime()
	{
		return (double)glfwGetTime();
	}
	double WindowsTime::ImplGetMiliseconds()
	{
    return m_deltaTime * 1000.0f;
	}
	float WindowsTime::ImplGetTimeScale()
	{
		return m_timeScale;
	}
	void WindowsTime::ImplSetTimeScale(float newScale)
	{
		m_timeScale = newScale;
	}
}
