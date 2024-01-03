#pragma once

#include "glm/glm.hpp"

namespace Endeavor
{
    class Camera
    {
    public:
        Camera(glm::vec2 pos = glm::vec2(0.0f, 0.0f), float width = 800, float height = 600);
        glm::mat4& GetViewMatrix() { return m_View; }
        glm::mat4& GetProjectionMatrix() { return m_Projection; }
        glm::vec2 GetWorldFromScreen(glm::vec2 screenPos, glm::vec2 screenDimensions);
        void Update();

    public:
        float width = 0;
        float height = 0;
        glm::vec2 position = glm::vec2(0.f);

    private:
        glm::mat4 m_Projection;
        glm::mat4 m_View;
    };
}