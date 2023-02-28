#pragma once
#include "entt/entt.hpp"
#include "Renderer.hpp"

class RenderSystem
{
public:
    RenderSystem(glm::vec2 dimensions);
    void update(std::shared_ptr<entt::registry> registry);

private:
    std::shared_ptr<Renderer> mRenderer;
};