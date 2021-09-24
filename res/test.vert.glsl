#version 330 core

layout(location = 0) in vec3 l_Pos;

void main()
{
	vec3 pos = l_Pos;
	pos.x *= 9.0f/16.0;
	gl_Position = vec4(pos, 1.0f);
}
