#pragma once

#include "gbpch.h"

#include "GB/Core.h"
#include "GB\Layer.h"
#include "Material.h"
#include "RenderObject.h"
namespace GB
{

	class GBAPI Renderer : public Layer
	{
	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnRender() override;
		virtual void OnImguiRender() override;

		virtual void Begin();
		virtual void End();
	private:

		void RenderEditorObj(float *position, float *scale, float *rotator, int *changeTex, float *color, bool *move_mouse);
		void CameraEditor();
		void MaterialEditor(RenderObject* renobj, char* pathbuff);
		void AlphaRender(bool active);
		std::vector<RenderObject*> m_renderObjects;
		std::vector<Texture*> m_textures;
	};



}
