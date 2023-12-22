#pragma once

#include "glm/glm.hpp"

namespace Endeavor
{
    class Camera
    {
    public:
        Camera(glm::vec2 pos = glm::vec2(0.0f, 0.0f), float width = 800, float height = 600);
        glm::mat4& GetViewMatrix() { return mView; }
        glm::mat4& GetProjectionMatrix() { return mProjection; }
        glm::vec2 GetWorldFromScreen (glm::vec2 screenPos, glm::vec2 screenDimensions);
        void Update();

    public:
        float width = 0;
        float height = 0;
        glm::vec2 position = glm::vec2(0.f);

    private:
        glm::mat4 mProjection;
        glm::mat4 mView;
    };
}