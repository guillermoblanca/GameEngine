#pragma once

#include "gbpch.h"

#include "GB/Core.h"
#include "GB\Layer.h"
#include "Material.h"
#include "RenderObject.h"

namespace GB
{
	//todo: refactor class to singleton instance 
	class GBAPI Renderer : public Layer
	{
	public:

		enum class RenderMode { Lines	  = 0x0001,
								LinesLoop = 0x0002,
								Triangles = 0x0004};
		Renderer();
		~Renderer();
		inline static Renderer& Get() { return *m_singleton; }
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnRender();
		virtual void OnImguiRender() override;

		virtual void Begin();
		virtual void End();//todo: not working

		void PushObj(IRender* obj);
		void PushOverLay(IRender* obj);
		void PopObj(IRender* obj);
		void PopOverlay(IRender* obj);

		inline IRender* GetRenderobj(unsigned int index) { return m_renderObjects[index]; }
		void SetRenderMode(RenderMode mode);
	private:
		static Renderer *m_singleton;
		
		std::vector<IRender*> m_renderObjects;
		std::vector<Material*> m_materials;
		std::vector<Texture*> m_textures;
		
		RenderMode mode;
		unsigned int m_renderIndex;

		void AlphaRender(bool active);

	};



}
