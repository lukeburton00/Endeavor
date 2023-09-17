#pragma once

#include "graphics/vao.hpp"
#include "graphics/vertex.hpp"
#include "graphics/camera.hpp"
#include "graphics/texture_2d.hpp"
#include "graphics/shader.hpp"

#include <string>
#include <vector>
#include <memory>

namespace Endeavor
{
    class Texture2D;
    class Shader;
    
    class SpriteBatch
    {
    public:

        static int numDrawCalls;

        SpriteBatch();

        void init();
        
        void begin(std::shared_ptr<Camera>& camera);

        void draw(const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& color, std::shared_ptr<Texture2D> texture, std::shared_ptr<Shader> shader);

        void drawSubTexture(const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& color, 
            std::shared_ptr<Texture2D> texture, std::shared_ptr<Shader> shader, 
            const glm::vec2& spriteOffset, const glm::vec2& spriteSize);

        void flush();

        void setProjectionMatrix(const glm::mat4& projection);
        void setViewMatrix(const glm::mat4& view);


    private:
        VAO mVAO;
        GLuint mVBO;
        GLuint mEBO;
        int numVertices;

        std::shared_ptr<Texture2D> mCurrentTexture;
        std::shared_ptr<Shader> mCurrentShader;

        std::vector<Vertex> mVertexBuffer;
        std::vector<int> mIndexBuffer;
        
        glm::mat4 mProjectionMatrix;
        glm::mat4 mViewMatrix;
    };
} // namespace Endeavor

