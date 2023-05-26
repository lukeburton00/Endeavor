#pragma once

#include "graphics/vao.hpp"
#include "glm/glm.hpp"
#include <string>

namespace Endeavor
{
    class Renderer
    {
    public:
        Renderer();
        void drawQuadImmediate(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color, std::string& texture);
        void setViewMatrix(const glm::mat4& viewMatrix);
        void setProjectionMatrix(const glm::mat4& projectionMatrix);

    private:
        VAO mQuadVAO;
        glm::mat4 mViewMatrix;
        glm::mat4 mProjectionMatrix;
        void createQuadPrimitive();
    };
} // namespace Endeavor