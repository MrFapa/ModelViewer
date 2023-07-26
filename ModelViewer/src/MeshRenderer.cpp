#include "MeshRenderer.h"
#include "OpenGLLogger.h"


MeshRenderer::MeshRenderer()
{

	glGenVertexArrays(1, &m_VAO);
	Bind();

	// Vertex Buffer
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(float), vertexPositions.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// Index Buffer
	m_IBOSize = static_cast<GLsizei>(indices.size()) * sizeof(unsigned int);
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IBOSize * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	Unbind();
	
}

MeshRenderer::~MeshRenderer() 
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void MeshRenderer::Bind() const
{
	glBindVertexArray(m_VAO);
}

void MeshRenderer::Unbind() const
{
	glBindVertexArray(0);
}

void MeshRenderer::Draw() const
{
	glDrawElements(GL_TRIANGLES, m_IBOSize, GL_UNSIGNED_INT, 0);
}

bool MeshRenderer::SetData(Mesh::MeshDataType key, const std::vector<float>& data)
{
	switch(key)
	{
		
	}
}

int MeshRenderer::GetCountFromMeshDataType(Mesh::MeshDataType dataType)
{
	switch (dataType)
	{
	case Mesh::MeshDataType::Position:
		return 3;
	case Mesh::MeshDataType::Normal:
		return 3;
	case Mesh::MeshDataType::UV:
		return 2;
	default:
		return 0;
	}
}








