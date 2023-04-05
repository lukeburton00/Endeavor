#pragma once

#include "Scene/Scene.hpp"
#include "ECS/Entity/Entity.hpp"

namespace Endeavor
{
    class Behavior
    {
    public:

        Behavior(Entity entity, std::shared_ptr<Scene> scene)
        {
            parent = entity;
            mScene = scene;
        }

        virtual ~Behavior(){}

        virtual void start(){}

        virtual void update(const float& deltaTime){}

    protected:
        Entity parent;
        std::shared_ptr<Scene> mScene;
    };
} // namespace Endeavor