#pragma once
#ifdef _WIN32
#include <glew.h>
#else
#include <GL/glew.h>
#endif

class Texture2D
{
public:
    GLuint mID;

    void bind();
};