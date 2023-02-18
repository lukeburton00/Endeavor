#pragma once
#include "Component.hpp"
#include <vector>

class GameObject
{
public:
    int id;

    GameObject()
    {
        mTransform = nullptr;
        mSprite = nullptr;
    };

    std::shared_ptr<Transform> addTransform()
    {
        mTransform = std::make_shared<Transform>();
        return mTransform;
    }

    std::shared_ptr<Transform> getTransform() const
    {
        return mTransform;
    }

    std::shared_ptr<Sprite> addSprite()
    {
        mSprite = std::make_shared<Sprite>();
        return mSprite;
    }

    std::shared_ptr<Sprite> getSprite() const
    {
        return mSprite;
    }

    virtual void update(float deltaTime){};

private:
    std::shared_ptr<Transform> mTransform;
    std::shared_ptr<Sprite> mSprite;
};