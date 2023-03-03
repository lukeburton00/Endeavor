#pragma once
#include "Scene.hpp"


class Behavior
{
public:

    Behavior(Entity entity, std::shared_ptr<Scene> scene)
    {
        parent = entity;
        mScene = scene;
    }

    virtual void start(){}

    virtual void update(float deltaTime){}

protected:
    Entity parent;
    std::shared_ptr<Scene> mScene;
};