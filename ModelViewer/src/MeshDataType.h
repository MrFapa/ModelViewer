#pragma once
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

enum class MeshDataType
{
    Invalid = 0,
    Vertex,
    Position,
    Index,
    Normal,
    UV
};

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};