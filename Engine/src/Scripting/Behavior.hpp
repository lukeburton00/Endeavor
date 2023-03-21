#pragma once
#include "Scene.hpp"
#include "Entity.hpp"

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