#include "SpriteBatcher.hpp"

SpriteBatcher::SpriteBatcher()
{
    printf("SpriteBatcher initialize\n");

    mVAO.generate();
    mVAO.bind();
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    mVAO.unbind();

    mTextureName = "GridTexture";
    printf("SpriteBatcher initialize finished\n");

    mViewProjection = glm::mat4(1.0f);
    mViewProjection = glm::ortho(0.0f, 1000.0f, 800.0f, 0.0f, -0.1f, 0.1f);
}

void SpriteBatcher::draw(glm::vec2 pos, glm::vec2 scale, glm::vec4 color, std::string textureName)
{
    // if (mTextureName != textureName)
    // {
    //     flush();
    //     mTextureName = textureName;
    // }

    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x, pos.y), glm::vec2(1.0f, 1.0f), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x + scale.x, pos.y), glm::vec2(1.0f, 0.0f), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x, pos.y + scale.y), glm::vec2(0.0f, 0.0f), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x + scale.x, pos.y), glm::vec2(1.0f, 0.0f), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x, pos.y + scale.y), glm::vec2(0.0f, 0.0f), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x + scale.x, pos.y + scale.y), glm::vec2(1.0f, 1.0f), color));
}

void SpriteBatcher::flush()
{
    // if (mTextureName == "")
    // {
    //     printf("No texture name specified.\n");
    //     return;
    // }

    auto shader = AssetManager::getShader("BatchShader");
    auto texture = AssetManager::getTexture(mTextureName);
    shader->use();
    texture->bind();
    mVAO.bind();
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertexBuffer.size(), &mVertexBuffer[0], GL_STATIC_DRAW);

    shader->setMat4("view_projection", mViewProjection);

    glDrawArrays(GL_TRIANGLES, 0, mVertexBuffer.size());

    mVAO.unbind();
    mVertexBuffer.clear();
}