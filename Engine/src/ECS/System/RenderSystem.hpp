#pragma once

#include "entt/entt.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/SpriteBatcher/SpriteBatcher.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Endeavor
{
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
} // namespace Endeavor