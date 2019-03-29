#pragma once
#include "GB\Layer.h"

#include "GB\Events\ApplicationEvent.h"
#include "GB\Events\KeyEvent.h"
#include "GB\Events\MouseEvent.h"

namespace GB
{
	
	class GBAPI ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach()override;
		virtual void OnDetach()override;
		virtual void OnImguiRender() override;

		void Begin();
		void End();
	private:
		
		float m_time = 0.0f;
	};
}