#include "RenderSystem.hpp"
#include "Sprite.hpp"
#include "Transform.hpp"

RenderSystem::RenderSystem(glm::vec2 dimensions)
{
    mRenderer = std::make_unique<Renderer>(dimensions);
    mSpriteBatcher = std::make_unique<SpriteBatcher>();

}

void RenderSystem::update(std::shared_ptr<entt::registry> &registry)
{
    auto group = registry->group<Sprite>(entt::get<Transform>);
    for (auto& entity : group)
    {
        auto &transform = group.get<Transform>(entity);
        auto &sprite = group.get<Sprite>(entity);

        //mRenderer->drawQuadImmediate(glm::vec2(transform.position.x, transform.position.y), glm::vec2(transform.scale.x, transform.scale.y), sprite.color, sprite.textureTag);
        //mSpriteBatcher->draw(glm::vec2(transform.position.x, transform.position.y), glm::vec2(transform.scale.x, transform.scale.y), sprite.color, sprite.textureTag);
    }

    //mSpriteBatcher->flush();
}