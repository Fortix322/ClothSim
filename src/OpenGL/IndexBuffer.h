#pragma once

#include "glad/glad.h"

#include <cstdint>

class IndexBuffer
{
public:

	IndexBuffer(uint32_t count);

	~IndexBuffer();

	void Bind() const;

	void Unbind() const;

	void StreamData(const void* data, uint32_t size, int32_t offset);

private:

	unsigned int m_RendererID;
	
};

