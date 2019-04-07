#include "gbpch.h"
#include "RenderObject.h"
#include "glad\glad.h" 

#include "glad\glad.h" 
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"


namespace GB
{


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