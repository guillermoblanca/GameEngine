#include "gbpch.h"

#include "IndexBuffer.h"
#include "glad\glad.h"



GB::IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):  m_RendererID(0), m_Count(0)
{				  

}
GB::IndexBuffer::~IndexBuffer()
{
}


void GB::IndexBuffer::Bind()const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

}

void GB::IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
