#pragma once

class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer();

	void Bind();
	void Unbind();

private:
	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_IBO;

};