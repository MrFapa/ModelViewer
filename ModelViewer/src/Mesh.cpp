#include "Mesh.h"
#include "MeshRenderer.h"

Mesh::Mesh()
{
	m_MeshRenderer = MeshRenderer();
    for (int i = static_cast<int>(MeshDataType::Position); i <= static_cast<int>(MeshDataType::UV); ++i) {
        auto dataType = static_cast<MeshDataType>(i);

        m_MeshData[dataType] = std::vector<float>();
    }
}

Mesh::~Mesh()
{
}

bool Mesh::UploadToMeshRenderer()
{
	for(auto iterator = m_MeshData.begin(); iterator != m_MeshData.end(); ++iterator)
	{
		MeshDataType key = iterator->first;
		m_MeshRenderer.
	}
}
