#include "graphics/texture_2d.hpp"

#include "stb_image.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

Endeavor::Texture2D::Texture2D(GLuint id)
{
    mID = id;
}

GLuint Endeavor::Texture2D::getID() const
{
	return mID;
}

void Endeavor::Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, mID);
}

std::shared_ptr<Endeavor::Texture2D> Endeavor::loadTexture2DFromFile(const char * texturePath)
{
	stbi_set_flip_vertically_on_load(true);  
    GLuint texture_id;
    std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>(texture_id);
    glGenTextures(1, &texture_id);

    texture->bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 4);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
		texture->width = width;
		texture->height = height;
    }

    else
    {
        printf("ERROR: Couldn't load texture from path %s\n", texturePath);
    }

    stbi_image_free(data);

    return texture;
}

bool Endeavor::Texture2D::operator==(const std::shared_ptr<Texture2D> rhs) const
{
    return (mID == rhs->getID());
}
