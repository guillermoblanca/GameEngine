#pragma once
#include "GB\Core.h"

#include "Material.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
namespace GB
{
	enum  ERenderMode { NONE = -1, BLEND = 0 };
	class GBAPI RenderObject
	{
	public:

		 RenderObject(const unsigned int *data , unsigned int count, Material * mat) : m_ib(data, count) , m_mat(mat)
		{
										 
			const float positions[]
			{
				-0.5f,-0.5f, 0.0f, 0.0f,
				 0.5f,-0.5f, 1.0f, 0.0f,
				 0.5f, 0.5f, 1.0f, 1.0f,
				-0.5f, 0.5f, 0.0f, 1.0f
			};


			VertexBuffer vb(positions, 4 * 4 * sizeof(float));
			VertexArray m_va;
			VertexBufferLayout m_layout;

			m_layout.Push<float>(2);
			m_layout.Push<float>(2);
			m_va.AddBuffer(vb, m_layout);

			

			m_ib.Bind();
		}
		void UnBind();
		void Render();
		void SetRenderMode(ERenderMode mode);

		inline Material* GetMat() { return m_mat; }
	private:
		IndexBuffer m_ib;
		Material * m_mat;
	};
}