#pragma once

#include "entt/entt.hpp"

namespace Endeavor
{
    class PhysicsSystem
    {
    public:
        PhysicsSystem();
        void update(std::shared_ptr<entt::registry> &registry, float deltaTime);
    private:
        float mElapsedTime;
    };
} // namespace Endeavor