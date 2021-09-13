#pragma once

#include <array>
#include "src/OpenGL/OpenGL.h"

class BatchRenderer
{
public:

	BatchRenderer(const char* vertShader, const char* fragShader);

	~BatchRenderer();

	void Draw();

	void Flush();

	void StreamData(const void* data, uint32_t size);

	void SetLayout(const VertexLayout& layout);

private:

	Shader m_ShaderProgram;

	VertexBuffer m_VertexBuffer;
	IndexBuffer m_IndexBuffer;
	VertexArray m_VertexArray;

	uint32_t offset = 0;

	static const uint32_t s_MaxQubes = 1;
	static const uint32_t s_VertBufSize = s_MaxQubes * 4 * sizeof(Vertex);
	static const uint32_t s_IndBufSize = s_MaxQubes * 6;

};

