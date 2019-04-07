#include "gbpch.h"
#include "RenderObject.h"
#include "glad\glad.h" 

#include "glad\glad.h" 
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"


namespace GB
{

	RenderObject::RenderObject(const float *positions,unsigned int size, const unsigned int *data, unsigned int count, Material * mat) : m_ib(data, count), m_mat(mat)
	{

		VertexBuffer vb(positions,size);
		VertexArray m_va;
		VertexBufferLayout m_layout;

		m_layout.Push<float>(2);
		m_layout.Push<float>(2);
		m_va.AddBuffer(vb, m_layout);



		m_ib.Bind();

	}
	void RenderObject::UnBind()
	{
		m_ib.Unbind();
	}
	void RenderObject::Render()
	{
		m_mat->Bind();
		m_ib.Bind();
		glDrawElements(GL_TRIANGLES, m_ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	void RenderObject::SetRenderMode(ERenderMode mode)
	{
		switch (mode)
		{
		case GB::NONE:
			glDisable(GL_BLEND);
			break;
		case GB::BLEND:
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			break;
		}
	}
}