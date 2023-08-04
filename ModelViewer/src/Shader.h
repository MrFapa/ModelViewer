#pragma once
#include <string>
#include <glm/gtc/matrix_transform.hpp>

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
	void Shader::SetUniformMat4(const std::string& name, glm::mat4 matrix);

private:
	void CreateShader(const std::string &vsSource, const std::string &fsSource);
	unsigned int CompileShader(const unsigned int type, const std::string& shaderSource);
	std::string ReadShaderSource(const std::string &filepath) const;
	

};
