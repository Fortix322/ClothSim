#include "Renderer.h"

#include <array>

struct Vertex
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

struct RendererStorage
{
	static const uint32_t MaxQuads = 1000;
	static const uint32_t MaxVertices = MaxQuads * 4 * sizeof(Vertex);
	static const uint32_t MaxIndices = MaxQuads * 6;

	Vertex* data;
	Vertex* dataPtr;

	Shader shader;
	VertexArray vao;
	IndexBuffer ebo;
	VertexBuffer vbo;

	unsigned int QuadsCount = 0;

	RendererStorage(const char* vertShader, const char* fragShader)
		: ebo(MaxIndices), vbo(MaxVertices), shader(vertShader, fragShader)
	{
		data = new Vertex[MaxVertices];
		dataPtr = data;
	}

	~RendererStorage()
	{
		delete[] data;
	}
};

static RendererStorage* s_Storage;

void Renderer::Init(const char* vertShader, const char* fragShader)
{
	s_Storage = new RendererStorage(vertShader, fragShader);

	s_Storage->vao.Bind();
	s_Storage->vbo.Bind();
	s_Storage->ebo.Bind();

	s_Storage->vao.AddBuffer(s_Storage->vbo, Vertex::GetLayout());

	unsigned int* indicies = new unsigned int[RendererStorage::MaxIndices];

	uint32_t offset = 0;
	for (uint32_t i = 0; i < RendererStorage::MaxIndices; i += 6)
	{
		indicies[0 + i] = 0 + offset;
		indicies[1 + i] = 1 + offset;
		indicies[2 + i] = 2 + offset;

		indicies[3 + i] = 1 + offset;
		indicies[4 + i] = 2 + offset;
		indicies[5 + i] = 3 + offset;

		offset += 4;
	}

	s_Storage->ebo.StreamData(indicies, s_Storage->MaxIndices, 0);

	delete[] indicies;
}

void Renderer::Shutdown()
{
	delete s_Storage;
}

void Renderer::DrawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color)
{
	if (s_Storage->QuadsCount >= RendererStorage::MaxQuads)
	{
		Renderer::DrawSubmit();
		Renderer::Flush();
	}

	s_Storage->QuadsCount++;

	*s_Storage->dataPtr++ = { glm::vec3(pos.x - size.x / 2.0f, pos.y - size.y / 2.0f, 0.0f), color };
	*s_Storage->dataPtr++ = { glm::vec3(pos.x + size.x / 2.0f, pos.y - size.y / 2.0f, 0.0f), color };
	*s_Storage->dataPtr++ = { glm::vec3(pos.x - size.x / 2.0f, pos.y + size.y / 2.0f, 0.0f), color };
	*s_Storage->dataPtr++ = { glm::vec3(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f, 0.0f), color };

	s_Storage->vbo.StreamData(s_Storage->data, (uint64_t)s_Storage->dataPtr - (uint64_t)s_Storage->data, 0);
}

void Renderer::DrawSubmit()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, s_Storage->QuadsCount * 6, GL_UNSIGNED_INT, 0);
}

void Renderer::Flush()
{
	s_Storage->vbo.InvalidateBufferData();
	s_Storage->QuadsCount = 0;
	s_Storage->dataPtr = s_Storage->data;
}
