#pragma once

#include "OpenGL/OpenGL.h"

#include "glm/glm/glm.hpp"

enum class eLayers
{
	UI = 0,
	L1,
	L2,
	L3,
	L4,
	L5,
	L6,
	L7,
	L8,
	L9,
	L10
};

class Renderer
{
public:

	static void Init(const char* vertShader, const char* fragShader);

	static void Shutdown();

	static void DrawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color, eLayers layer = eLayers::UI);

	static void DrawSubmit();

	static void Flush();
};
