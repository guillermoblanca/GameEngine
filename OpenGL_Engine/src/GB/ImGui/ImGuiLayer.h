#pragma once
#include "gbpch.h"

namespace GB
{
	//todo: pasar esto a archivo independiente
	class GBAPI Layer
	{
	public:
		Layer(const std::string& name = "Layer") {}
		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		//virtual void OnEvent() {}

		inline const std::string& GetName() { return m_DebugName; }
	protected:
		const std::string m_DebugName;
	};

	class GBAPI ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach()override;
		void OnDetach()override;
		void OnUpdate()override;
	private:
		float m_time = 0.0f;
	};
}