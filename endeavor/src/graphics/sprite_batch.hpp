#pragma once

#include "graphics/vao.hpp"
#include "graphics/vertex.hpp"
#include "graphics/camera.hpp"

#include <string>
#include <vector>

namespace Endeavor
{
    class SpriteBatch
    {
    public:

        static int numDrawCalls;

        SpriteBatch();

        void init();
        
        void begin(std::shared_ptr<Camera>& camera);

        void draw(const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& color, const std::string& textureName, const std::string& shaderName);

        void drawSubTexture(const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& color, 
            const std::string& textureName, const glm::vec2& spriteOffset, const glm::vec2& spriteSize, 
            const std::string& shaderName);

        void flush();

        void setProjectionMatrix(const glm::mat4& projection);
        void setViewMatrix(const glm::mat4& view);


    private:
        VAO mVAO;
        GLuint mVBO;
        GLuint mEBO;

        int numVertices;

        std::string mTextureName;
        std::string mShaderName;

        std::vector<Vertex> mVertexBuffer;
        std::vector<int> mIndexBuffer;
        
        glm::mat4 mProjectionMatrix;
        glm::mat4 mViewMatrix;
    };
} // namespace Endeavor

