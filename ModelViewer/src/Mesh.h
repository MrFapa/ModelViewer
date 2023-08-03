#pragma once

#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "MeshDataType.h"
#include "MeshRenderer.h"

class Mesh
{
public:
    Mesh();
    ~Mesh();

    void InitMeshRenderer();
    MeshRenderer& GetMeshRenderer() { return m_MeshRenderer; }

    const std::string& GetName() const { return m_Name; }
    void SetName(const std::string& name) { m_Name = name; }

    const std::vector<glm::vec3>& GetPositions() const { return m_Positions; }
    void SetPositions(const std::vector<glm::vec3>& positions) { m_Positions = positions; }

    const std::vector<glm::vec3>& GetNormals() const { return m_Normals; }
    void SetNormals(const std::vector<glm::vec3>& normals) { m_Normals = normals; }

    const std::vector<glm::vec2>& GetUVs() const { return m_UVs; }
    void SetUVs(const std::vector<glm::vec2>& uvs) { m_UVs = uvs; }

    const std::vector<unsigned int>& GetIndices() const { return m_Indices; }
    void SetIndices(const std::vector<unsigned int>& indices) { m_Indices = indices; }

    const std::vector<Vertex>& GetVertices() const { return m_Vertices; }
    void SetVertices(const std::vector<Vertex>& vertices) { m_Vertices = vertices; }

private:
    std::string m_Name;
    std::vector<glm::vec3> m_Positions;
    std::vector<glm::vec3> m_Normals;
    std::vector<glm::vec2> m_UVs;
    std::vector<unsigned int> m_Indices;
    std::vector<Vertex> m_Vertices;
    MeshRenderer m_MeshRenderer;
};
