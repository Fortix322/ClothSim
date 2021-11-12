#version 330 core

layout(location = 0) in vec3 l_Pos;
layout(location = 1) in vec4 l_Color;
layout(location = 2) in vec2 l_UV;
layout(location = 3) in float l_TexID;

out vec4 color;

void main()
{
	vec3 pos = l_Pos;
	//pos.x *= 9.0f/16.0;
	gl_Position = vec4(pos, 1.0f);

	color = l_Color;
}
