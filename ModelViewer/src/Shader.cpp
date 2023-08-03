#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "OpenGLLogger.h"

Shader::Shader(const std::string &vsPath, const std::string &fsPath) 
{
	std::string vsSource = ReadShaderSource(vsPath);
	std::string fsSource = ReadShaderSource(fsPath);
	CreateShader(vsSource, fsSource);
}

Shader::~Shader()
{
	glDeleteProgram(m_Id);
}

void Shader::Bind()
{
	glUseProgram(m_Id);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetUniform1f(const std::string &name, float value)
{
	unsigned int location = glGetUniformLocation(m_Id, name.c_str());
	glUniform1f(location, value);
}


void Shader::CreateShader(const std::string &vsSource, const std::string &fsSource) 
{
	m_Id = glCreateProgram();
	if (m_Id == 0)
		std::cout << "Shader Program could not be created" << std::endl;
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vsSource);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fsSource);

	glAttachShader(m_Id, vs);
	glAttachShader(m_Id, fs);
	glLinkProgram(m_Id);
	glUseProgram(m_Id);
}

unsigned int Shader::CompileShader(const unsigned type, const std::string& shaderSource)
{
	unsigned int shaderID = glCreateShader(type);
	const char* sourceChar = shaderSource.c_str();
	glShaderSource(shaderID, 1, &sourceChar, nullptr);
	glCompileShader(shaderID);

	GLint compiled;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		std::string typeString = (type == GL_VERTEX_SHADER) ? "Vertex " : "Fragment ";
		std::cout << typeString << "was not compiled successfully!" << std::endl;

		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(shaderID, 1024, &log_length, message);
		shaderID = 0;
	}
	return shaderID;
}


std::string Shader::ReadShaderSource(const std::string& filepath) const
{
	std::ifstream t(filepath);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}