#pragma once

#include <unordered_map>
#include <vector>

#include "MeshRenderer.h"
class Mesh
{

public:
	Mesh();
	~Mesh();

	bool UploadToMeshRenderer();

	enum class MeshDataType
	{
		Invalid = 0,
		Position,
		Index,
		Normal,
		UV
	};

	MeshRenderer& GetMeshRenderer() { return m_MeshRenderer; }

	const std::vector<float>& GetVertexPositions() const { return m_MeshData.at(MeshDataType::Position); }
	const std::vector<float>& GetIndices() const { return m_MeshData.at(MeshDataType::Index); }
	const std::vector<float>& GetNormals() const { return m_MeshData.at(MeshDataType::Normal); }
	const std::vector<float>& GetUVs() const { return m_MeshData.at(MeshDataType::UV); }

	const std::vector<float>& GetMeshData(MeshDataType dataType) const { return m_MeshData.at(dataType); }
	

private:
	std::unordered_map<MeshDataType, std::vector<float>> m_MeshData;

	MeshRenderer m_MeshRenderer;
};