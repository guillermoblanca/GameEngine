#pragma once
#include "GB/Utils/UniqueID.h"

namespace GB
{
	class Component
	{
	public:
		Component() {}

		virtual void OnUpdate(float DeltaTime) = 0;
		virtual void ImguiRender() = 0;

		bool operator ==(const Component& other)
		{
			return other.m_identifier.id == other.m_identifier.id;
		}

	protected:

		static UniqueID m_identifier;
	};

}
//
//class SpriteRenderer : public Component
//{
//public:
//
//	std::unique_ptr<Texture2D> sprite;
//	bool flipX;
//	bool flipY;
//	color color;
//	int layer;
//
//
//	void ImguiRender();
//};
