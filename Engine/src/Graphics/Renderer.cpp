#include "Renderer.hpp"

Renderer::Renderer(glm::vec2 dimensions)
{
    createQuadPrimitive();
    setViewport(dimensions);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

}

void Renderer::drawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color, std::string& textureName)
{
    Shader shader = *AssetManager::getShader("DefaultShader");
    Texture2D texture = *AssetManager::getTexture(textureName);

    texture.bind();

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(position, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, 1.0f));

    shader.use();
    shader.setMat4("model", modelMatrix);
    shader.setMat4("view", viewMatrix);
    shader.setMat4("projection", mProjectionMatrix);
    shader.setVec4("color", color);

    mQuadVAO.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    mQuadVAO.unbind();
}

void Renderer::createQuadPrimitive()
{
    float vertices[] = {
        // Position  // Texture
        1.0f,  1.0f, 1.0f, 1.0f, // top right
        1.0f, 0.0f, 1.0f, 0.0f,// bottom right
        0.0f, 0.0f, 0.0f, 0.0f,// bottom left
        0.0f, 1.0f, 0.0f, 1.0f// top left 
    };

    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    mQuadVAO.generate();
    mQuadVAO.bind();

    GLuint VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    mQuadVAO.unbind();
}

void Renderer::setViewport(const glm::vec2& dimensions)
{
    mProjectionMatrix = glm::ortho(0.0f, dimensions.x, dimensions.y, 0.0f, -1.0f, 1.0f);
}