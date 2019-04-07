#include "gbpch.h"

#include "IndexBuffer.h"
#include "glad\glad.h"



GB::IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):  m_RendererID(0), m_Count(count)
{				  
	GB_CORE_ASSERT(sizeof(unsigned int) == sizeof(GLuint), "Unsigned int not equal Opengl");
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
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
