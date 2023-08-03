// Mesh.cpp

#include "Mesh.h"
#include "MeshRenderer.h"

Mesh::Mesh()
{
	m_MeshRenderer = MeshRenderer();
}

Mesh::~Mesh()
{
}

void Mesh::InitMeshRenderer()
{
    m_MeshRenderer = MeshRenderer(m_Vertices);
}
