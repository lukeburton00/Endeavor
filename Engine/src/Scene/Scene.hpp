#pragma once
#include "entt/entt.hpp"

class Scene
{
public:
    Scene() : mRegistry(std::make_shared<entt::registry>()){}

    entt::entity createEntity();
    void destroyEntity(entt::entity entity);
    std::shared_ptr<entt::registry> getRegistry();

    template<typename T> void addComponent(entt::entity entity)
    {
        mRegistry->emplace_or_replace<T>(entity);
    }

    template<typename T> void removeComponent(entt::entity entity)
    {
        mRegistry->remove<T>(entity);
    }

private:
    std::shared_ptr<entt::registry> mRegistry;
};