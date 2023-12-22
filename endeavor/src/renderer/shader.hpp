#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <memory>
#include <string>

namespace Endeavor
{
	class Shader
	{
	public:
		Shader(uint32_t id);
		~Shader() = default;
		void Use();

		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetVec2(const std::string& name, glm::vec2 value) const;
		void SetVec4(const std::string& name, glm::vec4 value) const;
		void SetMat4(const std::string& name, glm::mat4 value) const;

		static std::shared_ptr<Shader> LoadFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	private:
		uint32_t mID = 0;
	};
}