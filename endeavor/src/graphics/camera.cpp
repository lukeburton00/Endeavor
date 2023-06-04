#include "camera.hpp"

#include "glm/gtc/matrix_transform.hpp"

Endeavor::Camera::Camera(glm::vec2 pos, float w, float h)
{
    position = pos;
    width = w;
    height = h;
    mView = glm::mat4(1.0f);
    updateMatrices();
}

void Endeavor::Camera::updateMatrices()
{
    mProjection = glm::ortho(-width / 2, width / 2, height / 2, -height / 2, -0.1f, 0.1f);
    mView = glm::mat4(1.0f);
    mView = glm::translate(mView, glm::vec3(-position.x, -position.y, 0.0f));
}

glm::vec2 Endeavor::Camera::getWorldPositionFromScreen(glm::vec2 screenPos, glm::vec2 screenDimensions)
{
    glm::vec2 pos = glm::unProject(glm::vec3(screenPos.x, screenPos.y, 0), mView, mProjection, glm::vec4(0,screenDimensions.y,screenDimensions.x,-screenDimensions.y));
    return pos;
}