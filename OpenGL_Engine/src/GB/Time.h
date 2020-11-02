#pragma once
#include "GB\Core.h"
namespace GB
{

	class GBAPI TimeStep
	{
	public:
		TimeStep(float time = 0.0f) : m_Time(time)
		{

		}

		operator float() const { return m_Time; }
		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:

		float m_Time;
	};

	class GBAPI Time
	{
	public:
		inline static double DeltaTime() { return s_instance->Impl_DeltaTime(); }
		inline static double GetTime() { return s_instance->ImplGetTime(); }
		inline static double GetMiliseconds() { return s_instance->ImplGetMiliseconds(); }
		inline static float GetTimeScale() { return s_instance->ImplGetTimeScale(); }
		inline static void SetTimeScale(float newScale) { return s_instance->ImplSetTimeScale(newScale); }
	protected:
		virtual double Impl_DeltaTime() = 0;
		virtual double ImplGetTime() = 0;
		virtual double ImplGetMiliseconds() = 0;
		virtual float ImplGetTimeScale() = 0;
		virtual void ImplSetTimeScale(float newScale) = 0;
	private:
		static Time* s_instance;
	};
}