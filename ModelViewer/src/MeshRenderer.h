#pragma once
#include <vector>
#include "MeshDataType.h"

class MeshRenderer
{
public:
    MeshRenderer() : m_VBO(0), m_VAO(0),m_IBO(0), m_IBOSize(0) {}
    MeshRenderer(const std::vector<Vertex>& vertices);
    ~MeshRenderer();

    void Init(const std::vector<Vertex>& vertices);
    void Bind() const;
    void Unbind() const;

    void Draw() const;

private:

    unsigned int m_VBO;
    unsigned int m_VAO;
    unsigned int m_IBO;
    
    unsigned int m_IBOSize;
};
