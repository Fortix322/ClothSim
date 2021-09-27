#pragma once

#include "OpenGL/OpenGL.h"

#include "glm/glm/glm.hpp"

class Renderer
{
public:

	static void Init(const char* vertShader, const char* fragShader);

	static void Shutdown();

	static void DrawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color);

	static void DrawSubmit();

	static void Flush();
};
