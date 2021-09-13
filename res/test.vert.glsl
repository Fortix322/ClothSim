#version 330 core

layout(location = 0) in vec3 l_Pos;

void main()
{
	gl_Position = vec4(l_Pos, 1.0f);
}
