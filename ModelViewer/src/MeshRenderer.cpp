#include "MeshRenderer.h"
#include "OpenGLLogger.h"
#include "MeshDataType.h"

MeshRenderer::MeshRenderer(const std::vector<Vertex>& vertices)
{
    Init(vertices);
}

MeshRenderer::~MeshRenderer()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void MeshRenderer::Init(const std::vector<Vertex>& vertices)
{
    // todo upgrade this
    std::vector<unsigned int> indices(vertices.size());
    for (int i = 0; i < vertices.size(); i++)
    {
        indices[i] = i;
    }

    GLCall(glGenVertexArrays(1, &m_VAO));
    GLCall(glBindVertexArray(m_VAO));

    GLCall(glGenBuffers(1, &m_VBO));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
    GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW););

    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));
    GLCall(glEnableVertexAttribArray(0));

    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float))));
    GLCall(glEnableVertexAttribArray(1));

    GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float))));
    GLCall(glEnableVertexAttribArray(2));

    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    GLCall(glBindVertexArray(0));

    m_IBOSize = indices.size();
}


void MeshRenderer::Bind() const
{
    GLCall(glBindVertexArray(m_VAO));
}

void MeshRenderer::Unbind() const
{
    glBindVertexArray(0);
}

void MeshRenderer::Draw() const
{
    GLCall(glDrawElements(GL_TRIANGLES, m_IBOSize, GL_UNSIGNED_INT, (void*)0));
}