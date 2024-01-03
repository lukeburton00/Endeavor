#pragma once

#include "sprite.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "gl_vertex_array.hpp"
#include "gl_vertex_buffer.hpp"
#include "gl_element_buffer.hpp"

#include "glm/glm.hpp"

namespace Endeavor
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer() = default;
		
		static std::shared_ptr<Renderer> GetInstance();

		void Init();

		void Begin(Camera& camera);
		void RenderSprite(glm::vec2 position, Sprite& sprite);
		void Draw();

	private:
		GLVertexArray m_VAO;
		GLVertexBuffer m_VBO;
		GLElementBuffer m_EBO;
		glm::mat4 m_ViewProjection;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Texture> m_Texture;
	};
	
	static std::shared_ptr<Renderer> s_Instance = nullptr;
}