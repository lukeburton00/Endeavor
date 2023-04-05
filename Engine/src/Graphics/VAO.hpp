#pragma once
#ifdef _WIN32
#include <glew.h>
#else
#include <GL/glew.h>
#endif

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