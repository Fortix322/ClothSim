#include "VertexArray.h"

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &m_rendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_rendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& buffer, const VertexLayout& layout)
{
	buffer.Bind();
	const auto& elements = layout.GetElements();
	uint64_t offset = 0;
	for (uint32_t i = 0; i < elements.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, layout.GetStride(), (const void*)offset);
		offset += elements[i].count * elements[i].GetSizeOfType(elements[i].type);
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_rendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
