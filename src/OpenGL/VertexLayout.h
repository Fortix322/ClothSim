#pragma once

#include <vector>

#include "glad/glad.h"

struct VertexLayoutElements 
{
	unsigned int type;
	uint32_t count;
	bool normalized;

	static uint16_t GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		__debugbreak();
		return 0;
	}
};

class VertexLayout
{
public:

	VertexLayout() 
		: m_stride(0), m_elements()
	{ }

	~VertexLayout() { }

	template<typename T>
	void Push(uint32_t count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(uint32_t count)
	{
		m_elements.push_back({ GL_FLOAT, count, false });
		m_stride += count * VertexLayoutElements::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(uint32_t count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, false });
		m_stride += count * VertexLayoutElements::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(uint32_t count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, true });
		m_stride += count * VertexLayoutElements::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	const std::vector<VertexLayoutElements>& GetElements() const { return m_elements; }
	
	const uint32_t& GetStride() const { return m_stride; }

private:

	std::vector<VertexLayoutElements> m_elements;
	uint32_t m_stride;
};

