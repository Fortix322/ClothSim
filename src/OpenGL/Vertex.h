#pragma once

#include <array>

struct Vertex
{
	std::array<float, 3> position;
	std::array<float, 4> color;
	std::array<float, 2> uv;
	float texID;
};
