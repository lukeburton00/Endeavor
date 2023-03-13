#include "SpriteBatcher.hpp"

SpriteBatcher::SpriteBatcher()
{
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

    mTextureName = "";

    mViewMatrix = glm::mat4(1.0f);
    mProjectionMatrix = glm::mat4(1.0f);
}

void SpriteBatcher::draw(glm::vec2 pos, glm::vec2 scale, glm::vec4 color, std::string textureName)
{
    if (mTextureName != textureName)
    {
        flush();
        mTextureName = textureName;
    }

    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x, pos.y), glm::vec2(1.0f, 1.0f), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x + scale.x, pos.y), glm::vec2(1.0f, 0.0f), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x, pos.y + scale.y), glm::vec2(0.0f, 0.0f), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x + scale.x, pos.y), glm::vec2(1.0f, 0.0f), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x, pos.y + scale.y), glm::vec2(0.0f, 0.0f), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x + scale.x, pos.y + scale.y), glm::vec2(1.0f, 1.0f), color));
}

void SpriteBatcher::flush()
{
    if (mTextureName == "")
    {
        return;
    }

    auto shader = AssetManager::getShader("BatchShader");
    auto texture = AssetManager::getTexture(mTextureName);
    shader->use();
    texture->bind();
    mVAO.bind();
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertexBuffer.size(), &mVertexBuffer[0], GL_STATIC_DRAW);

    glm::mat4 viewProjection = mProjectionMatrix * mViewMatrix;

    shader->setMat4("view_projection", viewProjection);

    glDrawArrays(GL_TRIANGLES, 0, mVertexBuffer.size());

    mVAO.unbind();
    mVertexBuffer.clear();
}

void SpriteBatcher::setProjectionMatrix(const glm::mat4& projection)
{
    mProjectionMatrix = projection;
}

void SpriteBatcher::setViewMatrix(const glm::mat4& view)
{
    mViewMatrix = view;
}