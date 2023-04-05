#include "ECS/System/RenderSystem.hpp"

#include "ECS/Component/Sprite.hpp"
#include "ECS/Component/Transform.hpp"
#include "ECS/Component/Camera.hpp"
#include "Core/Input/Input.hpp"

Endeavor::RenderSystem::RenderSystem()
{
    mRenderer = std::make_unique<Renderer>();
    mSpriteBatcher = std::make_unique<SpriteBatcher>();
}

void Endeavor::RenderSystem::updateProjection(std::shared_ptr<entt::registry> &registry)
{
    auto cameraGroup = registry->group<Camera>(entt::get<Transform>);
    for (auto& entity : cameraGroup)
    {
        auto &camera = cameraGroup.get<Camera>(entity);
        auto &transform = cameraGroup.get<Transform>(entity);

        if (camera.isPrimary)
        {
            glm::mat4 viewMatrix = glm::mat4(1.0f);
            viewMatrix = glm::translate(viewMatrix, glm::vec3(-transform.position.x, transform.position.y, -transform.position.z));
            mRenderer->setViewMatrix(viewMatrix);
            mSpriteBatcher->setViewMatrix(viewMatrix);
        }
    }
}

void Endeavor::RenderSystem::update(std::shared_ptr<entt::registry> &registry)
{
    auto spriteGroup = registry->group<Sprite>(entt::get<Transform>);
    for (auto& entity : spriteGroup)
    {
        auto &transform = spriteGroup.get<Transform>(entity);
        auto &sprite = spriteGroup.get<Sprite>(entity);

        //mRenderer->drawQuadImmediate(glm::vec2(transform.position.x, transform.position.y), glm::vec2(transform.scale.x, transform.scale.y), sprite.color, sprite.textureTag);
        mSpriteBatcher->draw(glm::vec2(transform.position.x, transform.position.y), glm::vec2(transform.scale.x, transform.scale.y), sprite.color, sprite.textureTag);
    }

    mSpriteBatcher->flush();
}

void Endeavor::RenderSystem::setOrthographicProjectionMatrix(const float& width, const float& height)
{
    glm::mat4 projection = glm::ortho(0.0f, width, height, 0.0f, -0.1f, 0.1f);
    mRenderer->setProjectionMatrix(projection);
    mSpriteBatcher->setProjectionMatrix(projection);
}