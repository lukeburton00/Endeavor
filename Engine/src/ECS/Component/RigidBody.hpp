#pragma once

#include "glm/glm.hpp"

namespace Endeavor
{
    struct RigidBody
    {
        glm::vec3 velocity;

        RigidBody() : velocity(glm::vec3(0.0f, 0.0f, 0.0f)){}
    };
} // namespace Endeavor