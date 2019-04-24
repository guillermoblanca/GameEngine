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
	private:
		std::vector<IRender*> m_renderObjects;
		unsigned int m_renderIndex;
		static Renderer *m_singleton;
		void AlphaRender(bool active);

		void MaterialEditor(RenderObject* renobj, char* pathbuff);
		std::vector<Texture*> m_textures;

	};



}
