#pragma once
#include "GB\Core.h"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
namespace GB
{
	enum  ERenderMode { NONE = -1, BLEND = 0 };
	class GBAPI RenderObject
	{
	public:

		RenderObject(const unsigned int *data , unsigned int count) : m_ib(data, count)
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
		void Bind();
		void UnBind();
		void Render();
		void SetRenderMode(ERenderMode mode);
	private:
		IndexBuffer m_ib;
	};
}