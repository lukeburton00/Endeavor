#pragma once

#include <glad/glad.h>

#include <memory>
#include <string>

namespace Endeavor
{
    class Texture
    {
    public:
        Texture(uint32_t id);
        ~Texture() = default;
        uint32_t GetID() const;
        void Bind();
        static std::shared_ptr<Texture> LoadFromFile(const std::string& path);

    public:
        float width = 0; 
        float height = 0;

    private:
        uint32_t mID = 0;
    };
}