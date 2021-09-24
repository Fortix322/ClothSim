#pragma once

#include "VertexLayout.h"

#include <array>

struct Vertex
{
	std::array<float, 3> position;
	std::array<float, 4> color;
	std::array<float, 2> uv;
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
