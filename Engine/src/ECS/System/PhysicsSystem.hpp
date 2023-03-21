#pragma once
#include "entt/entt.hpp"

class PhysicsSystem
{
public:
    PhysicsSystem();
    void update(std::shared_ptr<entt::registry> &registry, float deltaTime);
private:
    float mElapsedTime;
};