#include "input.hpp"

#include "game.hpp"

#include "GLFW/glfw3.h"

namespace Endeavor
{
    bool Input::IsKeyPressed(const KeyCode code)
    {
        auto window = Game::GetInstance().GetWindow().GetNativeWindow();
        auto state = glfwGetKey(window, static_cast<int32_t>(code));
        return state == GLFW_PRESS;
    }

    bool Input::IsMouseButtonPressed(const MouseCode code)
    {
        auto window = Game::GetInstance().GetWindow().GetNativeWindow();
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(code));
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::GetMousePosition()
    {
        double x, y;
        glfwGetCursorPos(Game::GetInstance().GetWindow().GetNativeWindow(), &x, &y);
        return glm::vec2((float)x, (float)y);
    }
}