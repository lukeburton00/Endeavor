#include "RenderSystem.hpp"
#include "Sprite.hpp"
#include "Transform.hpp"

RenderSystem::RenderSystem(glm::vec2 dimensions)
{
    printf("RenderSystem constructor\n");
    mRenderer = std::make_shared<Renderer>(dimensions);
    printf("RenderSystem constructor finished\n");
}

void RenderSystem::update(std::shared_ptr<entt::registry> registry)
{
    auto view = registry->view<Sprite, Transform>();
    for (auto entity : view)
    {
        auto &transform = view.get<Transform>(entity);
        auto &sprite = view.get<Sprite>(entity);
        mRenderer->drawQuad(glm::vec2(transform.position.x, transform.position.y), glm::vec2(transform.scale.x, transform.scale.y), sprite.color, sprite.textureTag);
    }
}