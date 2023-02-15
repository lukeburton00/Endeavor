#include "VAO.hpp"

void VAO::generate()
{
    glGenVertexArrays(1, &mID);
}

void VAO::bind()
{
    glBindVertexArray(mID);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

