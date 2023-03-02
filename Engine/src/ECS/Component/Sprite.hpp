#pragma once
#include <string>
#include "glm/glm.hpp"

struct Sprite
{
    std::string textureTag;
    glm::vec4 color;

    Sprite() : textureTag("DefaultTexture"), color(glm::vec4(1.0f,1.0f,1.0f,1.0f)) {}
    Sprite(glm::vec4 colorVector) : textureTag("DefaultTexture"), color(colorVector) {}

};