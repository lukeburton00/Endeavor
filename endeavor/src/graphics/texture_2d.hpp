#pragma once

#include <GL/glew.h>

namespace Endeavor
{
    class Texture2D
    {
    public:
        GLuint mID;

        void bind();
    };
} // namespace Endeavor