#include "gbpch.h"
#include "WindowsTime.h"
#include "GLFW\glfw3.h"

namespace GB
{
	Time* WindowsTime::s_instance = new WindowsTime();
	float WindowsTime::m_deltaTime = 0;

	float WindowsTime::Impl_DeltaTime()
	{
		double r = glfwGetTime() - m_deltaTime;
		m_deltaTime = glfwGetTime();
		return r;
	}

	float WindowsTime::ImplGetTime()
	{
		return (float)glfwGetTime();
	}
	float WindowsTime::ImplGetFPS()
	{
		static int nFrames = 0;
		static int initTime = Time::GetTime();
		static float fps = 0;
		double now = Time::GetTime();
		nFrames++;
		if (now - initTime >= 1.0f)
		{
			fps = nFrames;
			nFrames = 0;
			initTime++;
		}
		return fps;
	}
}
