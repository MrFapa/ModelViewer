#pragma once
#include <vector>
#include "Mesh.h"

class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer();

	void Bind() const;
	void Unbind() const;

	void Draw() const;

	bool SetData(Mesh::MeshDataType key, const std::vector<float>& data );

private:
	int GetCountFromMeshDataType(Mesh::MeshDataType dataType);


	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_IBO;

	unsigned int m_IBOSize;
};
