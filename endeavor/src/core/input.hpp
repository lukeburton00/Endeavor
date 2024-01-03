#pragma once

#include "keycodes.hpp"
#include "mousecodes.hpp"

#include "glm/glm.hpp"

namespace Endeavor
{
    namespace Input
    {
        bool IsKeyPressed(const KeyCode code);
        bool IsMouseButtonPressed(const MouseCode code);
        glm::vec2 GetMousePosition();
    };
}