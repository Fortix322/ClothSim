#pragma once

#include "OpenGL/VertexBuffer.h"
#include "OpenGL/VertexLayout.h"

class VertexArray
{
public:

	VertexArray();

	~VertexArray();

	void AddBuffer(const VertexBuffer& buffer, const VertexLayout& layout);

	void Bind() const;

	void Unbind() const;

private:
	unsigned int m_RendererID;
};

