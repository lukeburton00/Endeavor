#include "graphics/sprite_batch.hpp"

#include "graphics/asset_manager.hpp"

int Endeavor::SpriteBatch::numDrawCalls = 0;

Endeavor::SpriteBatch::SpriteBatch()
{
    mTextureName = "";
    mShaderName = "";
    numVertices = 0;
}

void Endeavor::SpriteBatch::init()
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
}
void Endeavor::SpriteBatch::begin(std::shared_ptr<Camera>& camera)
{
    setViewMatrix(camera->getViewMatrix());
    setProjectionMatrix(camera->getProjectionMatrix());
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

    mIndexBuffer.push_back(numVertices + 0);
    mIndexBuffer.push_back(numVertices + 1);
    mIndexBuffer.push_back(numVertices + 3);
    mIndexBuffer.push_back(numVertices + 1);
    mIndexBuffer.push_back(numVertices + 2);
    mIndexBuffer.push_back(numVertices + 3);

    numVertices += 4;
}

void Endeavor::SpriteBatch::drawSubTexture(const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& color, const std::string& textureName, const glm::vec2& spriteOffset, const glm::vec2& spriteSize, const std::string& shaderName)
{

    if (mTextureName != textureName)
    {
        flush();
        mTextureName = textureName;
        mTexture = AssetManager::getTexture(textureName);
        mTexture->bind();
    }

    if (mShaderName != shaderName)
    {
        flush();
        mShaderName = shaderName;
        mShader = AssetManager::getShader(shaderName);
        mShader->use();
    }

    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x + scale.x, pos.y),           glm::vec2(((spriteOffset.x + 1) * spriteSize.x) / mTexture->width, ((spriteOffset.y + 1) * spriteSize.y) / mTexture->height), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x + scale.x, pos.y + scale.y), glm::vec2(((spriteOffset.x + 1) * spriteSize.x) / mTexture->width, ((spriteOffset.y) * spriteSize.y) / mTexture->height), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x, pos.y + scale.y),           glm::vec2(((spriteOffset.x) * spriteSize.x) / mTexture->width, ((spriteOffset.y) * spriteSize.y) / mTexture->height), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x, pos.y),                     glm::vec2(((spriteOffset.x) * spriteSize.x) / mTexture->width, ((spriteOffset.y + 1) * spriteSize.y) / mTexture->height), color));

    mIndexBuffer.push_back(numVertices + 0);
    mIndexBuffer.push_back(numVertices + 1);
    mIndexBuffer.push_back(numVertices + 3);
    mIndexBuffer.push_back(numVertices + 1);
    mIndexBuffer.push_back(numVertices + 2);
    mIndexBuffer.push_back(numVertices + 3);

    numVertices += 4;
}

void Endeavor::SpriteBatch::flush()
{
    if (mTextureName == "" || mShaderName == "")
    {
        return;
    }

    mVAO.bind();
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertexBuffer.size(), &mVertexBuffer[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * mIndexBuffer.size(), &mIndexBuffer[0], GL_STATIC_DRAW);

    glm::mat4 viewProjection = mProjectionMatrix * mViewMatrix;

    mShader->setMat4("view_projection", viewProjection);

    glDrawElements(GL_TRIANGLES, mIndexBuffer.size(), GL_UNSIGNED_INT, 0);
    numDrawCalls++;

    mVAO.unbind();
    mVertexBuffer.clear();
    mIndexBuffer.clear();

    numVertices = 0;

}

void Endeavor::SpriteBatch::setProjectionMatrix(const glm::mat4& projection)
{
    mProjectionMatrix = projection;
}

void Endeavor::SpriteBatch::setViewMatrix(const glm::mat4& view)
{
    mViewMatrix = view;
}