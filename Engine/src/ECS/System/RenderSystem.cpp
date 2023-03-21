#include "RenderSystem.hpp"
#include "Sprite.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Input.hpp"

RenderSystem::RenderSystem()
{
    mRenderer = std::make_unique<Renderer>();
    mSpriteBatcher = std::make_unique<SpriteBatcher>();
}

void RenderSystem::updateProjection(std::shared_ptr<entt::registry> &registry)
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

void RenderSystem::update(std::shared_ptr<entt::registry> &registry)
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

void RenderSystem::setProjection(const glm::mat4 &projection)
{
    mRenderer->setProjectionMatrix(projection);
    mSpriteBatcher->setProjectionMatrix(projection);
}