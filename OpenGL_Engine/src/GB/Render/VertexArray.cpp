#include "gbpch.h"
#include "VertexArray.h"
#include "glad\glad.h"
GB::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

GB::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void GB::VertexArray::AddBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout)
{
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i=0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i,element.count, element.type, element.normalized, layout.GetStride(),(const void*)offset);
		offset += element.count* VertexBufferElement::GetSizeOfType(element.type);
	}
	

}

void GB::VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void GB::VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
