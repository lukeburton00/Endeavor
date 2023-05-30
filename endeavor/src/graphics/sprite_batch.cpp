#include "graphics/sprite_batch.hpp"

#include "graphics/asset_manager.hpp"

Endeavor::SpriteBatch::SpriteBatch()
{
    mVAO.generate();
    mVAO.bind();
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glGenBuffers(1, &mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    mVAO.unbind();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    mTextureName = "";
    mShaderName = "";


    mViewMatrix = glm::mat4(1.0f);
    mProjectionMatrix = glm::mat4(1.0f);

    quadNum = 0;
}

void Endeavor::SpriteBatch::draw(const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& color, const std::string& textureName, const std::string& shaderName)
{

    if (mTextureName != textureName)
    {
        flush();
        mTextureName = textureName;
    }

    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x + scale.x, pos.y),           glm::vec2(1.0f, 1.0f), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x + scale.x, pos.y + scale.y), glm::vec2(1.0f, 0.0f), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x, pos.y + scale.y),           glm::vec2(0.0f, 0.0f), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x, pos.y),                     glm::vec2(0.0f, 1.0f), color));

    mIndexBuffer.push_back(quadNum + 0);
    mIndexBuffer.push_back(quadNum + 1);
    mIndexBuffer.push_back(quadNum + 3);
    mIndexBuffer.push_back(quadNum + 1);
    mIndexBuffer.push_back(quadNum + 2);
    mIndexBuffer.push_back(quadNum + 3);

    quadNum += 4;
}

void Endeavor::SpriteBatch::drawSubTexture(const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& color, const std::string& textureName, const glm::vec2& spriteOffset, const glm::vec2& spriteSize, const std::string& shaderName)
{

    if (mTextureName != textureName)
    {
        flush();
        mTextureName = textureName;
    }

    auto texture = AssetManager::getTexture(textureName);

    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x + scale.x, pos.y),           glm::vec2(((spriteOffset.x + 1) * spriteSize.x) / texture->width, ((spriteOffset.y + 1) * spriteSize.y) / texture->height), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x + scale.x, pos.y + scale.y), glm::vec2(((spriteOffset.x + 1) * spriteSize.x) / texture->width, ((spriteOffset.y) * spriteSize.y) / texture->height), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x, pos.y + scale.y),           glm::vec2(((spriteOffset.x) * spriteSize.x) / texture->width, ((spriteOffset.y) * spriteSize.y) / texture->height), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x, pos.y),                     glm::vec2(((spriteOffset.x) * spriteSize.x) / texture->width, ((spriteOffset.y + 1) * spriteSize.y) / texture->height), color));

    mIndexBuffer.push_back(quadNum + 0);
    mIndexBuffer.push_back(quadNum + 1);
    mIndexBuffer.push_back(quadNum + 3);
    mIndexBuffer.push_back(quadNum + 1);
    mIndexBuffer.push_back(quadNum + 2);
    mIndexBuffer.push_back(quadNum + 3);

    quadNum += 4;
}

void Endeavor::SpriteBatch::flush()
{
    if (mTextureName == "")
    {
        return;
    }

    auto shader = AssetManager::getShader("default_shader");
    auto texture = AssetManager::getTexture(mTextureName);
    shader->use();
    texture->bind();
    mVAO.bind();
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertexBuffer.size(), &mVertexBuffer[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * mIndexBuffer.size(), &mIndexBuffer[0], GL_STATIC_DRAW);

    glm::mat4 viewProjection = mProjectionMatrix * mViewMatrix;

    shader->setMat4("view_projection", viewProjection);

    glDrawElements(GL_TRIANGLES, mIndexBuffer.size(), GL_UNSIGNED_INT, 0);

    mVAO.unbind();
    mVertexBuffer.clear();
    mIndexBuffer.clear();

    quadNum = 0;

}

void Endeavor::SpriteBatch::setProjectionMatrix(const glm::mat4& projection)
{
    mProjectionMatrix = projection;
}

void Endeavor::SpriteBatch::setViewMatrix(const glm::mat4& view)
{
    mViewMatrix = view;
}