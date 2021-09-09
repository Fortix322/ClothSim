#pragma once

#include "glad/glad.h"

#include <cstdint>

class IndexBuffer
{
public:

	IndexBuffer(uint64_t size);

	~IndexBuffer();

	void Bind() const;

	void Unbind() const;

	void StreamData(const void* data, uint64_t size, int64_t offset);

private:
	unsigned int m_rendererID;
};

