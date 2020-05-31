#pragma once
#include "GB\Core.h"
namespace GB
{
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