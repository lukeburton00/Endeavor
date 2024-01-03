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
        m_View = glm::mat4(1.0f);
        Update();
    }

    void Camera::Update()
    {
        m_Projection = glm::ortho(-width / 2, width / 2, height / 2, -height / 2, -1.f, 1.f);
        m_View = glm::translate(glm::mat4(1.f), glm::vec3(-position.x, -position.y, 0.f));
    }

    glm::vec2 Camera::GetWorldFromScreen(glm::vec2 screenPos, glm::vec2 screenDimensions)
    {
        return glm::unProject(glm::vec3(screenPos.x, screenPos.y, 0.f), m_View, m_Projection, glm::vec4(0.f, screenDimensions.y, screenDimensions.x, -screenDimensions.y));
    }
}