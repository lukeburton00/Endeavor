#include "gl_element_buffer.hpp"

namespace Endeavor
{
	GLElementBuffer::~GLElementBuffer()
	{
		Unbind();
		glDeleteBuffers(1, &m_ID);
	}

	void GLElementBuffer::Init()
	{
		glGenBuffers(1, &m_ID);
	}

	void GLElementBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void GLElementBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void GLElementBuffer::Push(uint32_t index)
	{
		m_Indices.push_back(index);
		m_NumIndices++;
	}

	void GLElementBuffer::Flush()
	{
		m_Indices.clear();
		m_NumIndices = 0;
	}

	void GLElementBuffer::BufferData()
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_Indices.size(), m_Indices.data(), GL_STATIC_DRAW);
	}
}