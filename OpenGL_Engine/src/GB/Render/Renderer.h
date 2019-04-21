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
		inline static Renderer& Get() { return *m_singleton; }
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnRender() override;
		virtual void OnImguiRender() override;

		virtual void Begin();
		virtual void End();
		std::vector<IRender*> m_renderObjects;
	private:

		static Renderer *m_singleton;
		void AlphaRender(bool active);
		void RenderEditorObj(RenderObject *object);
		void CameraEditor();
		void MaterialEditor(RenderObject* renobj, char* pathbuff);
		std::vector<Texture*> m_textures;

	};



}
