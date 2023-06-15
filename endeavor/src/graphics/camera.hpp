#pragma once

#include "glm/glm.hpp"

namespace Endeavor
{
    class Camera
    {
    public:
        float width, height;
        float screenWidth, screenHeight;
        glm::vec2 position;

        Camera(glm::vec2 pos, float width = 40, float height = 30);

        glm::mat4 getViewMatrix() const { return mView; }
        glm::mat4 getProjectionMatrix() const { return mProjection; }

        glm::vec2 getWorldFromScreen(glm::vec2 screenPos, glm::vec2 screenDimensions);

        void updateMatrices();

    private:
        glm::mat4 mProjection;
        glm::mat4 mView;
    };
} // namespace Endeavor