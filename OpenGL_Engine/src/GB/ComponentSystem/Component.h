#pragma once
#include "gbpch.h"
#include "GB\Core.h"

namespace GB
{

	class GBAPI Component
	{
	public:
		Component(std::string debugname = "Component") : m_debugname(debugname) {}

		virtual void OnUpdate() {};
		virtual void OnRender() {};

	private:
		std::string m_debugname;
		bool active;
	};

}