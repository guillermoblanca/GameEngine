#pragma once

#include "gbpch.h"
#include "GB/Core.h"
#include "GB\Layer.h"
#include "Material.h"

namespace GB
{
	enum EDrawMode
	{
		Line,
		Triangles
	};
	class GBAPI Renderer : public Layer
	{
	public:
		virtual void OnAttach() override;
		//virtual void OnDetach() override;
		virtual void OnRender() override;
		virtual void OnImguiRender() override;

		virtual void Begin();
		virtual void End();
	private:
		unsigned int ibo;
		unsigned int vao;
		Material material;

		std::vector<Material> m_Materials;
	};



}
