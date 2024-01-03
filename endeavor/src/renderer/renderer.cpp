#include "renderer.hpp"

#include "shader.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <iostream>

namespace Endeavor
{
	Renderer::Renderer()
	{
		m_ViewProjection = glm::mat4(1.f);
	}

    std::shared_ptr<Renderer> Renderer::GetInstance()
    {
        if (!s_Instance)
		{
			s_Instance = std::make_shared<Renderer>();
		}

		return s_Instance;
    }

    void Renderer::Init()
    {
		std::cout << "Renderer Init" << std::endl;
		m_VAO.Init();
		m_VAO.Bind();
		m_VBO.Init();
		m_EBO.Init();
		m_EBO.Bind();
		m_VAO.Unbind();

		m_Shader = Shader::LoadFromFile("../assets/shaders/vertex.glsl", "../assets/shaders/fragment.glsl");
		m_Texture = Texture::LoadFromFile("../assets/textures/default.jpg");
	}

	void Renderer::Begin(Camera& camera)
	{
		m_ViewProjection = camera.GetProjectionMatrix() * camera.GetViewMatrix();
	}

	void Renderer::RenderSprite(glm::vec2 position, Sprite& sprite)
	{
		m_EBO.Push(m_VBO.numVertices + 0);
		m_EBO.Push(m_VBO.numVertices + 1);
		m_EBO.Push(m_VBO.numVertices + 3);
		m_EBO.Push(m_VBO.numVertices + 1);
		m_EBO.Push(m_VBO.numVertices + 2);
		m_EBO.Push(m_VBO.numVertices + 3);

        m_VBO.Push(Vertex(glm::vec2(position.x + sprite.scale.x, position.y),					glm::vec2(((sprite.textureCoords.x + 1) * sprite.textureScale.x) / m_Texture->width, ((sprite.textureCoords.y + 1) * sprite.textureScale.y) / m_Texture->height), sprite.color));
        m_VBO.Push(Vertex(glm::vec2(position.x + sprite.scale.x, position.y + sprite.scale.y),	glm::vec2(((sprite.textureCoords.x + 1) * sprite.textureScale.x) / m_Texture->width, ((sprite.textureCoords.y) * sprite.textureScale.y) / m_Texture->height), sprite.color));
        m_VBO.Push(Vertex(glm::vec2(position.x, position.y + sprite.scale.y),					glm::vec2(((sprite.textureCoords.x) * sprite.textureScale.x) / m_Texture->width, ((sprite.textureCoords.y) * sprite.textureScale.y) / m_Texture->height), sprite.color));
        m_VBO.Push(Vertex(glm::vec2(position.x, position.y),									glm::vec2(((sprite.textureCoords.x) * sprite.textureScale.x) / m_Texture->width, ((sprite.textureCoords.y + 1) * sprite.textureScale.y) / m_Texture->height), sprite.color));

	}

	void Renderer::Draw()
	{
		m_VAO.Bind();
		m_VBO.Bind();
		m_EBO.Bind();
		m_VBO.BufferData();
		m_EBO.BufferData();

		m_Texture->Bind();
		m_Shader->SetMat4("view_projection", m_ViewProjection);
		m_Shader->Use();

		glDrawElements(GL_TRIANGLES, m_EBO.GetIndexCount(), GL_UNSIGNED_INT, 0);

		m_VAO.Unbind();
		m_VBO.Flush();
		m_EBO.Flush();
	}
}