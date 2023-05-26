#include "asset_manager.hpp"

#include "stb_image.h"

#include <iostream>
#include <sstream>
#include <fstream>

std::map<std::string, std::shared_ptr<Endeavor::Texture2D>> Endeavor::AssetManager::mTextures;
std::map<std::string, std::shared_ptr<Endeavor::Shader>> Endeavor::AssetManager::mShaders;

void Endeavor::AssetManager::loadShader(const std::string &name, const char * vertexPath, const char * fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;
	
	vertexShaderFile.open(vertexPath);
	fragmentShaderFile.open(fragmentPath);
	
	std::stringstream vertexShaderStream, fragmentShaderStream;
	
	vertexShaderStream << vertexShaderFile.rdbuf();
	fragmentShaderStream << fragmentShaderFile.rdbuf();
	
	vertexShaderFile.close();
	fragmentShaderFile.close();
		
	vertexCode = vertexShaderStream.str();
	fragmentCode = fragmentShaderStream.str();
	
	const char * vertexSource = vertexCode.c_str();
	const char * fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	
    #ifdef DEBUG

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};
    #endif
	
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	
    #ifdef DEBUG
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};
    #endif
	
    std::shared_ptr<Shader> shader = std::make_shared<Shader>();

	shader->mID = glCreateProgram();
	glAttachShader(shader->mID, vertexShader);
	glAttachShader(shader->mID, fragmentShader);
	glLinkProgram(shader->mID);
	
    mShaders[name] = shader;

    #ifdef DEBUG
	// print linking errors if any
	glGetProgramiv(shader->mID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(shader->mID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
    #endif
	  
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Endeavor::AssetManager::loadTexture2D(const std::string &name, const char * texturePath)
{
	stbi_set_flip_vertically_on_load(true);  
    std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>();
    glGenTextures(1, &texture->mID);

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
    }
    else
    {
        printf("Couldn't load texture\n");
    }
    stbi_image_free(data);

    mTextures[name] = texture;
}

std::shared_ptr<Endeavor::Shader> Endeavor::AssetManager::getShader(const std::string &name)
{
    return mShaders[name];
}

std::shared_ptr<Endeavor::Texture2D> Endeavor::AssetManager::getTexture(const std::string &name)
{
    return mTextures[name];
}