#pragma once
#include "entt/entt.hpp"
#include "Renderer.hpp"
#include "SpriteBatcher.hpp"

class RenderSystem
{
public:
    RenderSystem();
    void update(std::shared_ptr<entt::registry> &registry);
    void updateProjection(std::shared_ptr<entt::registry> &registry);
    void setProjection(const glm::mat4 &projection);

private:
    std::unique_ptr<Renderer> mRenderer;
    std::unique_ptr<SpriteBatcher> mSpriteBatcher;

};