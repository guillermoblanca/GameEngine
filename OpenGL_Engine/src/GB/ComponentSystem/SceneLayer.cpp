
#include "gbpch.h"
#include "SceneLayer.h"

namespace GB
{
	SceneLayer::SceneLayer() : Layer("SceneLayer")
	{

	}

	void SceneLayer::OnUpdate()
	{
		GB_CORE_WARN("SceneLayer update");
		for (auto obj : m_gameobjects)
		{
			obj->OnUpdate();
		}
	}
}