#pragma once

#include <GL/glew.h>

namespace Endeavor
{
    class VAO
    {
    public:
        void generate();
        void bind();
        void unbind();

    private:
        GLuint mID;
    };
} // namespace Endeavor