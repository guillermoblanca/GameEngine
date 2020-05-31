#pragma once
#include "GB\Core.h"
#include "GB\Time.h"
namespace GB
{
	class GBAPI WindowsTime : public Time
	{
	protected:
		virtual double Impl_DeltaTime();
		virtual double ImplGetTime();
		virtual double ImplGetMiliseconds();
		virtual float ImplGetTimeScale()override;
		virtual void ImplSetTimeScale(float newScale) override;
	private:
		static double m_deltaTime;
		static double m_lastTime;
		static double m_unscaledDeltaTime;
		static float m_timeScale;
		static long double m_time;
		
	};
}