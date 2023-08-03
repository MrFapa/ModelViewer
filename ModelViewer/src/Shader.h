#pragma once
#include <string>

class Shader
{
private:
	unsigned int m_Id = 0;
public:
	Shader(const std::string &vsPath, const std::string &fsPath);
	~Shader();

	void Bind();
	void Unbind();

	void SetUniform1f(const std::string &name, float value);

private:
	void CreateShader(const std::string &vsSource, const std::string &fsSource);
	unsigned int CompileShader(const unsigned int type, const std::string& shaderSource);
	std::string ReadShaderSource(const std::string &filepath) const;
	

};
