#pragma once

#include "src/OpenGL/VertexBuffer.h"
#include "src/OpenGL/VertexLayout.h"

class VertexArray
{
public:

	VertexArray();

	~VertexArray();

	void AddBuffer(const VertexBuffer& buffer, const VertexLayout layout);

	void Bind() const;

	void Unbind() const;

private:
	unsigned int m_rendererID;
};

