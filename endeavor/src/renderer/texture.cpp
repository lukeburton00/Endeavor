#include "texture.hpp"

#include <stb_image.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

namespace Endeavor
{
    Texture::Texture(uint32_t id)
    {
        mID = id;
    }

    uint32_t Texture::GetID() const
    {
        return mID;
    }

    void Texture::Bind()
    {
        glBindTexture(GL_TEXTURE_2D, mID);
    }

    std::shared_ptr<Texture> Texture::LoadFromFile(const std::string& path)
    {
        stbi_set_flip_vertically_on_load(true);
        uint32_t texture_id;
        glGenTextures(1, &texture_id);
        std::shared_ptr<Texture> texture = std::make_shared<Texture>(texture_id);

        texture->Bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 4);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            texture->width = width;
            texture->height = height;
        }

        else
        {
            printf("ERROR: Couldn't load texture from path %s\n", path.c_str());
        }

        stbi_image_free(data);

        std::cout << "Texture load successful" << std::endl;

        return texture;
    }
}
