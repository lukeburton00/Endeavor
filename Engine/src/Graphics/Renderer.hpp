#pragma once
#include "Shader.hpp"
#include "Texture2D.hpp"
#include "VAO.hpp"
#include "AssetManager.hpp"

class Renderer
{
public:
    Renderer(glm::vec2 dimensions);
    void drawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color, std::string& texture);
    void setViewport(const glm::vec2& dimensions);

private:
    VAO mQuadVAO;
    glm::mat4 mProjectionMatrix;
    void createQuadPrimitive();
};