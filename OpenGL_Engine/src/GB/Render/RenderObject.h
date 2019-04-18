#pragma once
#include "GB\Core.h"

#include "Material.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
namespace GB
{
	enum  ERenderMode
	{
		NONE  =	BIT(0),
		RED   =	BIT(1),
		GREEN = BIT(2),
		BLUE  =	BIT(3),
		ALPHA = BIT(4)
	};
	class GBAPI RenderObject
	{
	public:

		RenderObject(const float *positions, unsigned int size, const unsigned int *data, unsigned int count, Material * mat,float *pos);
		~RenderObject();
		void UnBind();
		void Render();
		void SetRenderMode(ERenderMode mode);

		inline Material* GetMat() { return m_mat; }
	private:
		VertexBuffer *m_vb;
		IndexBuffer m_ib;
		Material * m_mat;
	};
}