#pragma once

#include "entt/entt.hpp"

#include <string>

namespace Endeavor
{
    class Entity;
    class Scene
    {
    public:
        Scene() : mRegistry(std::make_shared<entt::registry>()){}

        Entity createEntity(const std::string& name);
        void destroyEntity(Entity entity);

        std::shared_ptr<entt::registry> getRegistry() { return mRegistry; }

    private:
        std::shared_ptr<entt::registry> mRegistry;
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
} // namespace Endeavor