#pragma once

#include <cstdint>

#include "glad/glad.h"


class VertexBuffer
{
public:

	VertexBuffer(uint32_t size);

	~VertexBuffer();

	void Bind() const;

	void Unbind() const;

	void StreamData(const void* data, uint32_t size, int32_t offset);

private:
	unsigned int m_RendererID;
};

