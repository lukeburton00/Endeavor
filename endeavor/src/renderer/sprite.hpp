#pragma once

#include <glm/glm.hpp>

namespace Endeavor
{
	struct Sprite
	{
		glm::vec2 scale = glm::vec2(10.f);
		glm::vec2 textureCoords = glm::vec2(0.f, 0.f);
		glm::vec2 textureScale = glm::vec2(1.f, 1.f);
		glm::vec4 color = glm::vec4(1.f);
	};
}