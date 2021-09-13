#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(uint32_t count)
{
	glCreateBuffers(1, &m_rendererID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	Unbind();
	glDeleteBuffers(1, &m_rendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::StreamData(const void* data, uint32_t size, int32_t offset)
{
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}
