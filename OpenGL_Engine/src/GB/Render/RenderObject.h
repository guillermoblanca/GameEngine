#pragma once
#include "GB\Core.h"

namespace GB
{
	enum  ERenderMode { NONE = -1, BLEND = 0 };
	class GBAPI RenderObject
	{
	public:

		void Create();
		void Bind();
		void UnBind();
		void Render();
		void SetRenderMode(ERenderMode mode);
	private:

	};
}