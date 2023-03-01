#pragma once
#include "entt/entt.hpp"

class Behavior
{
public:

    Behavior(entt::entity entity, std::shared_ptr<entt::registry> registry)
    {
        parent = entity;
        mRegistry = registry;
    }

    virtual void update(float deltaTime)
    {
        printf("Updating base behavior class...\n");
    }

protected:
    entt::entity parent;
    std::shared_ptr<entt::registry> mRegistry;
};