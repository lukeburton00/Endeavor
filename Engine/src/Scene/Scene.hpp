#pragma once
#include "entt/entt.hpp"

class Scene
{
public:
    Scene() : mRegistry(std::make_shared<entt::registry>()){}

    entt::entity createEntity();
    void destroyEntity(entt::entity entity);
    std::shared_ptr<entt::registry> getRegistry();

    template<typename T, typename... Args> void addComponent(entt::entity entity, Args &&...args)
    {
        mRegistry->emplace_or_replace<T>(entity, args...);
    }

    template<typename T> void removeComponent(entt::entity entity)
    {
        mRegistry->remove<T>(entity);
    }

private:
    std::shared_ptr<entt::registry> mRegistry;
};