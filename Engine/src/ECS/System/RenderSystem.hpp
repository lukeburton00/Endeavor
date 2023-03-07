#pragma once
#include "entt/entt.hpp"
#include "Renderer.hpp"
#include "SpriteBatcher.hpp"

class RenderSystem
{
public:
    RenderSystem(glm::vec2 dimensions);
    void update(std::shared_ptr<entt::registry> &registry);

private:
    std::unique_ptr<Renderer> mRenderer;
    std::unique_ptr<SpriteBatcher> mSpriteBatcher;

};