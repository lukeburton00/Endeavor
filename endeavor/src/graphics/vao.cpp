#include "graphics/vao.hpp"

void Endeavor::VAO::generate()
{
    glGenVertexArrays(1, &mID);
}

void Endeavor::VAO::bind()
{
    glBindVertexArray(mID);
}

void Endeavor::VAO::unbind()
{
    glBindVertexArray(0);
}

