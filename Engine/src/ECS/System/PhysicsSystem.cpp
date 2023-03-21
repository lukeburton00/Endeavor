#include "PhysicsSystem.hpp"
#include "Transform.hpp"
#include "RigidBody.hpp"
#include <iostream>

PhysicsSystem::PhysicsSystem()
{
    mElapsedTime = 0;
}

void PhysicsSystem::update(std::shared_ptr<entt::registry> &registry, float deltaTime)
{
    mElapsedTime += deltaTime;
    auto group = registry->group<Transform, RigidBody>();

    for (auto entity : group)
    {
        auto& rb = group.get<RigidBody>(entity);
        auto& transform = group.get<Transform>(entity);

        rb.velocity.y += 9.8f * deltaTime;
        
        transform.position.x += rb.velocity.x * deltaTime;
        transform.position.y += rb.velocity.y * deltaTime;
        transform.position.z += rb.velocity.z * deltaTime;

    }


}