#pragma once
#include "Scene.hpp"

class Behavior
{
public:

    Behavior(entt::entity entity, std::shared_ptr<Scene> scene)
    {
        parent = entity;
        mScene = scene;
    }

    virtual void start()
    {
        #ifdef DEBUG
        printf("Starting base behavior class...\n");
        #endif
    }

    virtual void update(float deltaTime)
    {
        #ifdef DEBUG
        printf("Updating base behavior class...\n");
        #endif
    }

protected:
    entt::entity parent;
    std::shared_ptr<Scene> mScene;
};