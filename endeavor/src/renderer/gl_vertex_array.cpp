#include "gl_vertex_array.hpp"

namespace Endeavor
{
    GLVertexArray::~GLVertexArray()
    {
        Unbind();
        glDeleteVertexArrays(1, &m_ID);
    }

    void GLVertexArray::Init()
    {
        glGenVertexArrays(1, &m_ID);
    }

    void GLVertexArray::Bind()
    {
        glBindVertexArray(m_ID);
    }

    void GLVertexArray::Unbind()
    {
        glBindVertexArray(0);
    }
}