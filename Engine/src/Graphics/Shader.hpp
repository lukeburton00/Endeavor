#pragma once
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#ifdef _WIN32
#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#else
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif



class Shader
{
public:
	GLuint mID;
	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec2(const std::string &name, glm::vec2 value) const;
	void setVec4(const std::string &name, glm::vec4 value) const;
	void setMat4(const std::string &name, glm::mat4 value) const;
};