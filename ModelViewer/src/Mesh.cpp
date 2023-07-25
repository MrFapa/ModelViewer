#include "Mesh.h"
#include "MeshRenderer.h"

Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices)
{
	m_MeshRenderer = new MeshRenderer(vertices, indices);
}

Mesh::~Mesh()
{
	delete m_MeshRenderer;
}

