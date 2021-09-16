#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "glad/glad.h"

struct ShaderSources
{
	std::string VertexShader;
	std::string FragmentShader;
};

class Shader
{
public:

	Shader(const std::string& vertShaderFile, const std::string& fragShaderFile);

	~Shader();

	void Bind();

	void Unbind();

private:

	ShaderSources ReadShadersFromFiles(const std::string& vertShaderFile, const std::string& fragShaderFile);

	unsigned int CompileShader(unsigned int type, const std::string& str);

private:
	unsigned int m_RendererID;
};

