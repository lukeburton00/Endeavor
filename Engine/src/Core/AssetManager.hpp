#pragma once

#include "Graphics/Texture2D.hpp"
#include "Graphics/Shader.hpp"

#include <map>
#include <memory>

namespace Endeavor 
{
    class AssetManager
    {
    public:
        static std::map<std::string, std::shared_ptr<Texture2D>> mTextures;
        static std::map<std::string, std::shared_ptr<Shader>> mShaders;

        static void loadShader(std::string &name, const char * vertexShaderPath, const char * fragmentShaderPath);
        static void loadTexture2D(std::string &name, const char * texturePath);
        
        static std::shared_ptr<Shader> getShader(const std::string &name);
        static std::shared_ptr<Texture2D> getTexture(const std::string &name);
    private:
        AssetManager(){};
    };
} // namespace Endeavor