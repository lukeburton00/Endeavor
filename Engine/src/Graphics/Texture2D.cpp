#include "Texture2D.hpp"

void Endeavor::Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, mID);
}