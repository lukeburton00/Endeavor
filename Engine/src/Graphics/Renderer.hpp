#pragma once
#include "Shader.hpp"
#include "Texture2D.hpp"
#include "VAO.hpp"
#include "ResourceManager.hpp"

class Renderer
{
public:
    Renderer();
    void drawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color);

private:
    VAO mQuadVAO;
    void createQuadPrimitive();
};