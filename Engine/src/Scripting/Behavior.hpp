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
        printf("Starting base behavior class...\n");
    }

    virtual void update(float deltaTime)
    {
        //printf("Updating base behavior class...\n");
    }

protected:
    entt::entity parent;
    std::shared_ptr<Scene> mScene;
};