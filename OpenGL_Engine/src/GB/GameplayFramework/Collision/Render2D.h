#pragma once
#include "GB\Core.h"
#include "GB\GameplayFramework\Entity.h"
namespace GB
{
	class Render2D : public Component
	{
	public:
		virtual void OnUpdate(float DeltaTime);
		virtual void ImguiRender();
		virtual int ID();
	};
}