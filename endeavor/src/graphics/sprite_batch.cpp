#include "graphics/sprite_batch.hpp"

int Endeavor::SpriteBatch::numDrawCalls = 0;

Endeavor::SpriteBatch::SpriteBatch()
{
    mCurrentShader = nullptr;
    mCurrentTexture = nullptr;
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

void Endeavor::SpriteBatch::draw(const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& color, std::shared_ptr<Endeavor::Texture2D> texture, std::shared_ptr<Endeavor::Shader> shader)
{
    if (mCurrentTexture != texture)
    {
        flush();
        mCurrentTexture = texture;
        mCurrentTexture->bind();
    }

    if (mCurrentShader != shader)
    {
        flush();
        mCurrentShader = shader;
        mCurrentShader->use();
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

void Endeavor::SpriteBatch::drawSubTexture(const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& color, std::shared_ptr<Texture2D> texture, std::shared_ptr<Shader> shader, const glm::vec2& spriteOffset, const glm::vec2& spriteSize)
{

    if (mCurrentTexture != texture)
    {
        flush();
        mCurrentTexture = texture;
        mCurrentTexture->bind();
    }

    if (mCurrentShader != shader)
    {
        flush();
        mCurrentShader = shader;
        mCurrentShader->use();
    }

    // Calculate texture coordinates based on sprite size and offset
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x + scale.x, pos.y),           glm::vec2(((spriteOffset.x + 1) * spriteSize.x) / mCurrentTexture->width, ((spriteOffset.y + 1) * spriteSize.y) / mCurrentTexture->height), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x + scale.x, pos.y + scale.y), glm::vec2(((spriteOffset.x + 1) * spriteSize.x) / mCurrentTexture->width, ((spriteOffset.y) * spriteSize.y) / mCurrentTexture->height), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x, pos.y + scale.y),           glm::vec2(((spriteOffset.x) * spriteSize.x) / mCurrentTexture->width, ((spriteOffset.y) * spriteSize.y) / mCurrentTexture->height), color));
    mVertexBuffer.push_back(Vertex(glm::vec2(pos.x, pos.y),                     glm::vec2(((spriteOffset.x) * spriteSize.x) / mCurrentTexture->width, ((spriteOffset.y + 1) * spriteSize.y) / mCurrentTexture->height), color));

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
    if (mCurrentTexture == nullptr || mCurrentShader == nullptr)
    {
        return;
    }

    mVAO.bind();
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertexBuffer.size(), &mVertexBuffer[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * mIndexBuffer.size(), &mIndexBuffer[0], GL_STATIC_DRAW);

    glm::mat4 viewProjection = mProjectionMatrix * mViewMatrix;

    mCurrentShader->setMat4("view_projection", viewProjection);

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