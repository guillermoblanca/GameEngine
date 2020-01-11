#pragma once
#include "GB\Core.h"
#include "GB\GameplayFramework\GameObject.h"
namespace GB
{
	class Render2D : public Component
	{
	public:
		virtual void Update();
		virtual void ImguiRender();
		virtual int ID();
	};
}