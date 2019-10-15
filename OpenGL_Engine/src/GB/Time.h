#pragma once
#include "GB\Core.h"
namespace GB
{
	class GBAPI Time
	{
	public: 
		inline static float DeltaTime() { return s_instance->Impl_DeltaTime(); }
		inline static float GetTime() { return s_instance->ImplGetTime(); }
		inline static float GetMiliseconds() { return s_instance->ImplGetMiliseconds(); }
	protected:
		virtual float Impl_DeltaTime() = 0;
		virtual float ImplGetTime() = 0;
		virtual float ImplGetMiliseconds() = 0;
	private:
		static Time* s_instance;
	};
}