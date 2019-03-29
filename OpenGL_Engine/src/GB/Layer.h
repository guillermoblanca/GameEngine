#pragma once
#include "Core.h"
#include "Events\Event.h"
namespace GB
{
	class GBAPI Layer
	{
	public:
		Layer(const std::string& name = "Layer") {}
		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}

		virtual void OnImguiRender() {}
		virtual void OnRender() {} //todo: temp

		inline const std::string& GetName() { return m_DebugName; }
	protected:
		const std::string m_DebugName;
	};

}
