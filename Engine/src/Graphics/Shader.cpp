#include "Graphics/Shader.hpp"

void Endeavor::Shader::use()
{
	glUseProgram(mID);
}

void Endeavor::Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(mID, name.c_str()), (int)value);
}

void Endeavor::Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
}

void Endeavor::Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
}

void Endeavor::Shader::setVec2(const std::string &name, glm::vec2 value) const
{
	glUniform2f(glGetUniformLocation(mID, name.c_str()), value.x, value.y);
}

void Endeavor::Shader::setVec4(const std::string &name, glm::vec4 value) const
{
	glUniform4f(glGetUniformLocation(mID, name.c_str()), value.x, value.y, value.z, value.w);
}

void Endeavor::Shader::setMat4(const std::string &name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}