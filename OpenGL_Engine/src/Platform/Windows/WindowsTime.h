#pragma once
#include "GB\Core.h"
#include "GB\Time.h"
namespace GB
{
	class GBAPI WindowsTime : public Time
	{
	protected:
		virtual float Impl_DeltaTime();
		virtual float ImplGetTime();
	private:
		static float m_deltaTime;
	};
}