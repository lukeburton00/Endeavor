#pragma once

#include <GL/glew.h>
#include <memory>

namespace Endeavor
{
    class Texture2D
    {
    public:
        float width, height;

        Texture2D(GLuint id);
        GLuint getID() const;
        void bind();

        bool operator==(const std::shared_ptr<Texture2D> rhs) const;

    private:
        GLuint mID;
    };

    std::shared_ptr<Texture2D> loadTexture2DFromFile(const char * texturePath);
} // namespace Endeavor