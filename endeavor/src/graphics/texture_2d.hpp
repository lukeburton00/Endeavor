#pragma once

#include <GL/glew.h>

namespace Endeavor
{
    class Texture2D
    {
    public:
        GLuint mID;
        float width, height;

        void bind();
    };
} // namespace Endeavor