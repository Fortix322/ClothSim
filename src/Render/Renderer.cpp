#include "Renderer.h"

#include <array>

struct QuadVertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	float texID;

	static VertexLayout GetLayout()
	{
		VertexLayout layout;

		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(2);
		layout.Push<float>(1);

		return layout;
	}

};

struct LineVertex
{
	glm::vec3 position;
	glm::vec4 color;

	static VertexLayout GetLayout()
	{
		VertexLayout layout;

		layout.Push<float>(3);
		layout.Push<float>(4);

		return layout;
	}

};


struct RendererStorage
{
	static const uint32_t s_MaxQuads = 10000;
	static const uint32_t s_MaxQuadVertices = s_MaxQuads * 4;
	static const uint32_t s_MaxQuadIndices = s_MaxQuads * 6;

	static const uint32_t s_MaxLines = 10000;
	static const uint32_t s_MaxLineVertices = s_MaxLines * 2;
	static const uint32_t s_MaxLineIndices = s_MaxLines * 2;

	QuadVertex* quads;
	QuadVertex* quadsPtr;

	LineVertex* lines;
	LineVertex* linesPtr;

	Shader shader;
	VertexArray quadVao;
	VertexArray lineVao;

	IndexBuffer quadEbo;
	IndexBuffer lineEbo;

	VertexBuffer quadVbo;
	VertexBuffer lineVbo;

	uint64_t quadsCount = 0;
	uint64_t linesCount = 0;

	RendererStorage(const char* vertShader, const char* fragShader)
		: quadEbo(s_MaxQuadIndices), quadVbo(s_MaxQuadVertices * sizeof(QuadVertex)), 
		lineEbo(s_MaxLineIndices), lineVbo(s_MaxLineVertices * sizeof(LineVertex)),
		shader(vertShader, fragShader)
	{
		quads = new QuadVertex[s_MaxQuadVertices];
		quadsPtr = quads;
		
		lines = new LineVertex[s_MaxLineVertices];
		linesPtr = lines;

		std::cout << s_MaxQuads << std::endl;
		std::cout << s_MaxQuadVertices << std::endl;
		std::cout << s_MaxQuadIndices << std::endl;

		std::cout << s_MaxLines << std::endl;
		std::cout << s_MaxLineVertices << std::endl;
		std::cout << s_MaxLineIndices << std::endl;
	}

	~RendererStorage()
	{
		delete[] quads;
		delete[] lines;
	}
};

static RendererStorage* s_Storage;

void Renderer::Init(const char* vertShader, const char* fragShader)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	s_Storage = new RendererStorage(vertShader, fragShader);

	s_Storage->quadVao.Bind();
	s_Storage->quadVao.AddBuffer(s_Storage->quadVbo, QuadVertex::GetLayout());

	s_Storage->lineVao.Bind();
	s_Storage->lineVao.AddBuffer(s_Storage->lineVbo, LineVertex::GetLayout());

	unsigned int* quadIndices = new unsigned int[RendererStorage::s_MaxQuadIndices];
	unsigned int* lineIndices = new unsigned int[RendererStorage::s_MaxLineIndices];

	uint32_t offset = 0;
	for (uint32_t i = 0; i < RendererStorage::s_MaxQuadIndices; i += 6)
	{
		quadIndices[0 + i] = 0 + offset;
		quadIndices[1 + i] = 1 + offset;
		quadIndices[2 + i] = 2 + offset;

		quadIndices[3 + i] = 1 + offset;
		quadIndices[4 + i] = 2 + offset;
		quadIndices[5 + i] = 3 + offset;

		offset += 4;
	}

	offset = 0;
	for (uint32_t i = 0; i < RendererStorage::s_MaxLineIndices; i += 2)
	{
		lineIndices[0 + i] = 0 + offset;
		lineIndices[1 + i] = 1 + offset;

		offset += 2;
	}

	s_Storage->quadEbo.StreamData(quadIndices, s_Storage->s_MaxQuadIndices, 0);
	s_Storage->lineEbo.StreamData(lineIndices, s_Storage->s_MaxLineIndices, 0);

	delete[] quadIndices;
	delete[] lineIndices;
}

void Renderer::Shutdown()
{
	delete s_Storage;
}

void Renderer::DrawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color, eLayers layer)
{
	if (s_Storage->quadsCount >= RendererStorage::s_MaxQuads)
	{
		Renderer::DrawSubmit();
		Renderer::Flush();
	}

	s_Storage->quadsCount++;

	*s_Storage->quadsPtr++ = { glm::vec3(pos.x - size.x / 2.0f, pos.y - size.y / 2.0f, (int)layer * 0.1f), color };
	*s_Storage->quadsPtr++ = { glm::vec3(pos.x + size.x / 2.0f, pos.y - size.y / 2.0f, (int)layer * 0.1f), color };
	*s_Storage->quadsPtr++ = { glm::vec3(pos.x - size.x / 2.0f, pos.y + size.y / 2.0f, (int)layer * 0.1f), color };
	*s_Storage->quadsPtr++ = { glm::vec3(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f, (int)layer * 0.1f), color };
}

void Renderer::DrawLine(glm::vec2 pos1, glm::vec2 pos2, glm::vec4 color, eLayers layer)
{
	if (s_Storage->linesCount >= RendererStorage::s_MaxLines)
	{
		Renderer::DrawSubmit();
		Renderer::Flush();
	}

	s_Storage->linesCount++;

	*s_Storage->linesPtr++ = { glm::vec3(pos1.x, pos1.y, (int)layer * 0.1f), color };
	*s_Storage->linesPtr++ = { glm::vec3(pos2.x, pos2.y, (int)layer * 0.1f), color };
}

void Renderer::DrawSubmit()
{
	s_Storage->quadVbo.StreamData(s_Storage->quads, (uint64_t)s_Storage->quadsPtr - (uint64_t)s_Storage->quads, 0);
	s_Storage->lineVbo.StreamData(s_Storage->lines, (uint64_t)s_Storage->linesPtr - (uint64_t)s_Storage->lines, 0);

	s_Storage->quadVao.Bind();
	s_Storage->quadEbo.Bind();
	s_Storage->quadVbo.Bind();
	glDrawElements(GL_TRIANGLES, s_Storage->quadsCount * 6, GL_UNSIGNED_INT, 0);
	
	s_Storage->lineVao.Bind();
	s_Storage->lineEbo.Bind();
	s_Storage->lineVbo.Bind();
	glDrawElements(GL_LINES, s_Storage->linesCount * 2, GL_UNSIGNED_INT, 0);
}

void Renderer::Flush()
{
	s_Storage->quadVbo.InvalidateBufferData();
	s_Storage->quadsCount = 0;
	s_Storage->quadsPtr = s_Storage->quads;

	s_Storage->lineVbo.InvalidateBufferData();
	s_Storage->linesCount = 0;
	s_Storage->linesPtr = s_Storage->lines;
}

void Renderer::ClearScreen(glm::vec4 color)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
