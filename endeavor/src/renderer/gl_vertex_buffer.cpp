#include "gl_vertex_buffer.hpp"

#include <iostream>

namespace Endeavor
{
	GLVertexBuffer::~GLVertexBuffer()
	{
		Unbind();
		glDeleteBuffers(1, &m_ID);
		m_Vertices = std::vector<Vertex>();
	}

	void GLVertexBuffer::Init()
	{
		glGenBuffers(1, &m_ID);
		Bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	}

	void GLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void GLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void GLVertexBuffer::Push(Vertex vertex)
	{
		m_Vertices.push_back(vertex);
		numVertices++;
	}

	void GLVertexBuffer::Flush()
	{
		m_Vertices.clear();
		numVertices = 0;
	}

	void GLVertexBuffer::BufferData()
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Vertices.size(), m_Vertices.data(), GL_STATIC_DRAW);
	}
}