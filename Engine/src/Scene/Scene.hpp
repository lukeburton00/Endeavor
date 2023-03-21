#pragma once
#include "entt/entt.hpp"

class Entity;
using Registry = entt::registry;

class Scene
{
public:
    Scene() : mRegistry(std::make_shared<Registry>()){}

    Entity createEntity();
    void destroyEntity(entt::entity entity);

    std::shared_ptr<Registry> getRegistry() { return mRegistry; }


private:
    std::shared_ptr<Registry> mRegistry;
    friend class Entity;

    template<typename T, typename... Args> T& addComponent(entt::entity entity, Args &&...args)
    {
        return mRegistry->emplace_or_replace<T>(entity, args...);
    }

    template<typename T> void removeComponent(entt::entity entity)
    {
        mRegistry->remove<T>(entity);
    }

    template<typename T> T& getComponent(entt::entity entity)
    {
        return mRegistry->get<T>(entity);
    }

};