#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(uint32_t size)
{
	glCreateBuffers(1, &m_rendererID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_rendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::StreamData(const void* data, uint32_t size, int32_t offset)
{
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
