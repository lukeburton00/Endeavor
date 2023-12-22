#include "camera.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

namespace Endeavor
{
    Camera::Camera(glm::vec2 pos, float w, float h)
    {
        position = glm::vec2(0,0);
        width = w;
        height = h;
        mView = glm::mat4(1.0f);
        Update();
    }

    void Camera::Update()
    {
        mProjection = glm::ortho(-width / 2, width / 2, height / 2, -height / 2, -1.f, 1.f);
        //std::cout << "Camera position X: " << position.x << " Camera position Y: " << position.y << std::endl;
        mView = glm::mat4(1.f);
        mView = glm::translate(mView, glm::vec3(-position.x, -position.y, 0.f));
    }

    glm::vec2 Camera::GetWorldFromScreen(glm::vec2 screenPos, glm::vec2 screenDimensions)
    {
        return glm::unProject(glm::vec3(screenPos.x, screenPos.y, 0.f), mView, mProjection, glm::vec4(0.f, screenDimensions.y, screenDimensions.x, -screenDimensions.y));
    }
}