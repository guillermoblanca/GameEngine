#pragma once
#include "GB\Core.h"
#include "Component.h"

namespace GB
{
	class GBAPI SpriteRender2D : public Component
	{
	public:
		SpriteRender2D() : Component("SpriteRender2D") {}
		virtual void OnRender() override;
	};
}