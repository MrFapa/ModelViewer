#pragma once
#include <vector>

class MeshRenderer
{
public:
	MeshRenderer(const std::vector<float> &vertexPositions, const std::vector<unsigned int> &indices);
	~MeshRenderer();

	void Bind() const;
	void Unbind() const;

	void Draw() const;

private:
	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_IBO;

	unsigned int m_IBOSize;
};
