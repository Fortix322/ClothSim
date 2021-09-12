#include "Shader.h"

Shader::Shader(const std::string& vertShaderFile, const std::string& fragShaderFile) 
{
	m_rendererID = glCreateProgram();

	ShaderSources shaders = ReadShadersFromFiles(vertShaderFile, fragShaderFile);

	unsigned int vertShader = CompileShader(GL_VERTEX_SHADER, shaders.VertexShader);
	unsigned int fragShader = CompileShader(GL_FRAGMENT_SHADER, shaders.FragmentShader);

	glAttachShader(m_rendererID, vertShader);
	glAttachShader(m_rendererID, fragShader);

	glLinkProgram(m_rendererID);

	Bind();

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_rendererID);
}

void Shader::Bind()
{
	glUseProgram(m_rendererID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

ShaderSources Shader::ReadShadersFromFiles(const std::string& vertShaderFile, const std::string& fragShaderFile) 
{
	
	std::fstream stream;
	std::string buffer;
	std::stringstream shaderStr[2];

	stream.open(vertShaderFile);

	if (stream.is_open())
	{
		std::cout << "Vertex Shader File is open";
	}
	else
	{
		std::cout << "Vertex Shader File isn`t open";
	}

	while (!stream.eof())
	{
		std::getline(stream, buffer);
		shaderStr[0] << buffer;
	}

	stream.close();
	stream.open(fragShaderFile);

	if (stream.is_open())
	{
		std::cout << "Fragment Shader File is open";
	}
	else
	{
		std::cout << "Fragment Shader File isn`t open";
	}

	while (!stream.eof())
	{
		std::getline(stream, buffer);
		shaderStr[1] << buffer;
	}

	return { shaderStr[0].str(), shaderStr[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& str)
{
	unsigned int shader;
	
	const char* source = str.c_str();

	shader = glCreateShader(type);

	glShaderSource(shader, 1, &source, NULL);

	glCompileShader(shader);

	return shader;
}
