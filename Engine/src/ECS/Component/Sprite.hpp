#pragma once

#include "glm/glm.hpp"

#include <string>

namespace Endeavor 
{
    struct Sprite
    {
        std::string textureTag;
        glm::vec4 color;

        Sprite() : textureTag("DefaultTexture"), color(glm::vec4(1.0f,1.0f,1.0f,1.0f)) {}
        Sprite(glm::vec4 colorVector, std::string texture) : textureTag(texture), color(colorVector) {}
    };
} // namespace Endeavor