#include "shader.hpp"

#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

namespace Endeavor
{


	Shader::Shader(uint32_t id)
	{
		mID = id;
	}

	void Shader::Use()
	{
		glUseProgram(mID);
	}

	void Shader::SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(mID, name.c_str()), (int)value);
	}

	void Shader::SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
	}

	void Shader::SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
	}

	void Shader::SetVec2(const std::string& name, glm::vec2 value) const
	{
		glUniform2f(glGetUniformLocation(mID, name.c_str()), value.x, value.y);
	}

	void Shader::SetVec4(const std::string& name, glm::vec4 value) const
	{
		glUniform4f(glGetUniformLocation(mID, name.c_str()), value.x, value.y, value.z, value.w);
	}

	void Shader::SetMat4(const std::string& name, glm::mat4 value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	std::shared_ptr<Shader> Shader::LoadFromFile(const std::string& vertexPath, const std::string& fragmentPath)
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

		const char* vertexSource = vertexCode.c_str();
		const char* fragmentSource = fragmentCode.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);

		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		GLuint shader_id = glCreateProgram();
		glAttachShader(shader_id, vertexShader);
		glAttachShader(shader_id, fragmentShader);
		glLinkProgram(shader_id);

		auto shader = std::make_shared<Shader>(shader_id);

		glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader_id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		std::cout << "Shader load successful" << std::endl;
		return shader;
	}
}