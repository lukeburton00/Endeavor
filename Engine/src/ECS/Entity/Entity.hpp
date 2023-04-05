#pragma once

#include "entt/entt.hpp"
#include "Scene/Scene.hpp"

namespace Endeavor
{
    class Entity
    {
    public:
        std::string name;

        Entity() : name("Entity") {}
        Entity(entt::entity handle, Scene* scene) : name("Entity"), mHandle(handle), mScene(scene){}

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