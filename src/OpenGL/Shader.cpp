#include "Shader.h"

Shader::Shader(const std::string& vertShaderFile, const std::string& fragShaderFile) 
{
	m_RendererID = glCreateProgram();

	ShaderSources shaders = ReadShadersFromFiles(vertShaderFile, fragShaderFile);

	unsigned int vertShader = CompileShader(GL_VERTEX_SHADER, shaders.VertexShader);
	unsigned int fragShader = CompileShader(GL_FRAGMENT_SHADER, shaders.FragmentShader);

	glAttachShader(m_RendererID, vertShader);
	glAttachShader(m_RendererID, fragShader);

	glLinkProgram(m_RendererID);

	Bind();

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind()
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::UniformMat4(const std::string& name, float* data)
{
	unsigned int location;
	location = glGetUniformLocation(m_RendererID, name.c_str());

	glUniformMatrix4fv(location, 1, GL_FALSE, data);
}

void Shader::UniformVec4(const std::string& name, float* data)
{
	unsigned int location;
	location = glGetUniformLocation(m_RendererID, name.c_str());

	glUniform4fv(location, 4, data);
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
		shaderStr[0] << buffer << '\n';
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
		shaderStr[1] << buffer << '\n';
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


	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);


	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}
