#pragma once
#include "entt/entt.hpp"

using Entity = entt::entity;
using Registry = entt::registry;

class Scene
{
public:
    Scene() : mRegistry(std::make_shared<Registry>()){}

    Entity createEntity();
    void destroyEntity(Entity entity);
    std::shared_ptr<Registry> getRegistry();

    template<typename T, typename... Args> void addComponent(Entity entity, Args &&...args)
    {
        mRegistry->emplace_or_replace<T>(entity, args...);
    }

    template<typename T> void removeComponent(Entity entity)
    {
        mRegistry->remove<T>(entity);
    }

private:
    std::shared_ptr<Registry> mRegistry;
};