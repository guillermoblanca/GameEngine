#pragma once
#include "GB\Core.h"

namespace GB
{
	class GraphicContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}