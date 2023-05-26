#include "graphics/texture_2d.hpp"

void Endeavor::Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, mID);
}