#include "PhysicsSystem.hpp"
#include "Transform.hpp"
#include <iostream>

PhysicsSystem::PhysicsSystem()
{
    mElapsedTime = 0;
}

void PhysicsSystem::update(std::shared_ptr<entt::registry> registry, float deltaTime)
{
    mElapsedTime += deltaTime;
    auto view = registry->view<Transform>();
}