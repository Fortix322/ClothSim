#include "BatchRenderer.h"

BatchRenderer::BatchRenderer(const char* vertShader, const char* fragShader) 
	: m_ShaderProgram(vertShader, fragShader), m_VertexArray(), m_VertexBuffer(s_VertBufSize), m_IndexBuffer(s_IndBufSize)
{

	m_VertexArray.Bind();
	m_VertexBuffer.Bind();
	m_IndexBuffer.Bind();

	std::array<unsigned int, s_IndBufSize> indicies;
	
	uint32_t offset = 0;
	for (uint32_t i = 0; i < indicies.size(); i += 6)
	{
		indicies[0 + i] = 0 + offset;
		indicies[1 + i] = 1 + offset;
		indicies[2 + i] = 2 + offset;

		indicies[3 + i] = 1 + offset;
		indicies[4 + i] = 2 + offset;
		indicies[5 + i] = 3 + offset;

		offset += 4;
	}

	m_IndexBuffer.StreamData(indicies.data(), indicies.size() * sizeof(unsigned int), 0);
}

BatchRenderer::~BatchRenderer()
{
}

void BatchRenderer::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//m_ShaderProgram.Bind();
	//m_VertexArray.Bind();
	//m_IndexBuffer.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//Flush();
}

void BatchRenderer::Flush()
{
	m_VertexBuffer.StreamData(0, s_MaxQubes * 4 * sizeof(Vertex), 0);
}

void BatchRenderer::StreamData(const void* data, uint32_t size)
{
	m_VertexBuffer.StreamData(data, size, offset);

	offset += size;

	if (offset >= s_VertBufSize)
		offset = 0;
}

void BatchRenderer::SetLayout(const VertexLayout& layout)
{
	m_VertexArray.AddBuffer(m_VertexBuffer, layout);
}
