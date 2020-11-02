#pragma once
#include "GB\Core.h"
#include "GB\GameplayFramework\Entity.h"
namespace GB
{
	class Render2D : public Component
	{
	public:
		Render2D() : Component("Render2D")
		{

		}
		void OnUpdate(float DeltaTime)override;
		void ImguiRender()override;
		virtual int ID();
	};

	class MeshRenderer : public Component
	{
	public:
	MeshRenderer() : Component("MeshRenderer"){}
	public:
		void OnUpdate(float DeltaTime) override;
		void ImguiRender() override;

	};
}