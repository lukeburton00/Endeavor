#pragma once

#include "graphics/texture_2d.hpp"
#include "graphics/shader.hpp"

#include <map>
#include <memory>

namespace Endeavor 
{
    class AssetManager
    {
    public:
        static std::map<std::string, std::shared_ptr<Texture2D>> mTextures;
        static std::map<std::string, std::shared_ptr<Shader>> mShaders;

        static void loadShader(const std::string &name, const char * vertexShaderPath, const char * fragmentShaderPath);
        static void loadTexture2D(const std::string &name, const char * texturePath);
        
        static std::shared_ptr<Shader> getShader(const std::string &name);
        static std::shared_ptr<Texture2D> getTexture(const std::string &name);
    private:
        AssetManager(){};
    };
} // namespace Endeavor