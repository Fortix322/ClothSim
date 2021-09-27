#pragma once

#include <cstdint>

#include "Glad/include/glad/glad.h"

class IndexBuffer
{
public:

	IndexBuffer(uint32_t count);

	~IndexBuffer();

	void Bind() const;

	void Unbind() const;

	void StreamData(const void* data, uint32_t count, int32_t offset);

private:

	unsigned int m_RendererID;
	
};

