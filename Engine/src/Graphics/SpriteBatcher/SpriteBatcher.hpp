#pragma once
#include "VAO.hpp"
#include "AssetManager.hpp"
#include "Vertex.hpp"
#include <string>
#include <vector>


class SpriteBatcher
{
public:
    SpriteBatcher();
    void draw(glm::vec2 pos, glm::vec2 scale, glm::vec4 color, std::string textureName);
    void flush();

private:
    VAO mVAO;
    GLuint mVBO;
    std::string mTextureName;
    std::vector<Vertex> mVertexBuffer;
    glm::mat4 mViewProjection;
};

