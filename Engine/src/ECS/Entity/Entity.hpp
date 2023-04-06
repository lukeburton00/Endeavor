#pragma once

#include "entt/entt.hpp"
#include "Scene/Scene.hpp"
#include "ECS/Component/Transform.hpp"

namespace Endeavor
{
    class Entity
    {
    public:

        Entity(){}

        Entity(entt::entity handle, Scene* scene) : mHandle(handle), mScene(scene){}

        template<typename T, typename... Args> T& addComponent(Args &&...args)
        {
            return mScene->addComponent<T>(mHandle, args...);
        }

        template<typename T> void removeComponent()
        {
            mScene->removeComponent<T>(mHandle);
        }

        template<typename T> T& getComponent()
        {
            return mScene->getComponent<T>(mHandle);
        }

        entt::entity getHandle() const { return mHandle; }

    private:
        entt::entity mHandle;
        Scene* mScene;
    };
} // namespace Endeavor