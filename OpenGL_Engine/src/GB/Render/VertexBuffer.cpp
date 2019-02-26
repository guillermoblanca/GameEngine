#include "gbpch.h"
#include "VertexBuffer.h" 
#include "glad\glad.h"

GB::VertexBuffer::VertexBuffer(const void * data, unsigned int size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

GB::VertexBuffer::~VertexBuffer()
{
	//todo: fix
	//glDeleteBuffers(1, &m_RendererID);
}

void GB::VertexBuffer::Bind()const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

}

void GB::VertexBuffer::Unbind()const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
