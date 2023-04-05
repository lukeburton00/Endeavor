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
    void setOrthographicProjectionMatrix(const float& width, const float& height);

private:
    std::unique_ptr<Renderer> mRenderer;
    std::unique_ptr<SpriteBatcher> mSpriteBatcher;

};