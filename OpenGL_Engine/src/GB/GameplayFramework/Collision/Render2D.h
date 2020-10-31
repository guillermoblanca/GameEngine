#pragma once
#include "GB\Core.h"
#include "GB\GameplayFramework\Entity.h"
namespace GB
{
	class Render2D : public Component
	{
	public:
		Render2D() : Component()
		{

		}
		void OnUpdate(float DeltaTime)override;
		void ImguiRender()override;
		virtual int ID();
	};

	class MeshRenderer : public Component
	{
	public:
	public:
		void OnUpdate(float DeltaTime) override;
		void ImguiRender() override;

	};
}