#pragma once

#include <vector>
class Mesh
{
public:
	Mesh(std::vector<float> vertices, std::vector<int> indices);
	~Mesh();

	class MeshRenderer* GetMeshRenderer() { return m_MeshRenderer; }

private:

	class MeshRenderer* m_MeshRenderer;
};