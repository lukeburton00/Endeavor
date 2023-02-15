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
    };

    void addTransform()
    {
        mTransform = std::make_shared<Transform>();
    }

    std::shared_ptr<Transform> getTransform() const
    {
        return mTransform;
    }
private:
    std::shared_ptr<Transform> mTransform;
};