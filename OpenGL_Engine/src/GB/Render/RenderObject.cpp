#include "gbpch.h"
#include "RenderObject.h"

#include "glad\glad.h" 
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"


namespace GB
{
	void RenderObject::Create()
	{
		const float positions[]
		{
			-0.5f,-0.5f, 0.0f, 0.0f,
			 0.5f,-0.5f, 1.0f, 0.0f,
			 0.5f, 0.5f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 1.0f
		};
		unsigned int indices[]
		{
			0,1,2,
			2,3,0
		};

		VertexBuffer vb(positions, 4 * 4 * sizeof(float));
		VertexArray m_va;
		VertexBufferLayout m_layout;
		
		m_layout.Push<float>(2);
		m_layout.Push<float>(2);
		m_va.AddBuffer(vb, m_layout);

		IndexBuffer ib(indices, 6);

		ib.Bind();
	}

	void RenderObject::Render()
	{

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		
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