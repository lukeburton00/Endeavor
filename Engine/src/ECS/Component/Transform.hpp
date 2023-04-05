#pragma once

#include "glm/glm.hpp"

namespace Endeavor 
{
    struct Transform
    {
        glm::vec3 position;
        glm::vec3 scale;

        Transform() : position(glm::vec3(0.0f, 0.0f, 0.0f)), scale(glm::vec3(10.0f, 10.0f, 10.0f)){}
        Transform(glm::vec3 positionParam, glm::vec3 scaleParam)
        {
            position = positionParam;
            scale = scaleParam;
        }
    };
} // namespace Endeavor