#pragma once

#include "Glad/include/glad/glad.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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

	void UniformMat4(const std::string& name, float* data);

	void UniformVec4(const std::string& name, float* data);


private:

	ShaderSources ReadShadersFromFiles(const std::string& vertShaderFile, const std::string& fragShaderFile);

	unsigned int CompileShader(unsigned int type, const std::string& str);

private:

	unsigned int m_RendererID;

};

