#pragma once
#include "Engine.hpp"

class PlayerController : public Behavior
{
    using Behavior::Behavior;

    void update(float deltaTime) override
    {
        auto &transform = mRegistry->get<Transform>(parent);

        if (Input::isKeyPressed("W"))
        {
            transform.position.y -= 100 * deltaTime;
        }

        if (Input::isKeyPressed("A"))
        {
            transform.position.x -= 100 * deltaTime;
        }

        if (Input::isKeyPressed("S"))
        {
            transform.position.y += 100 * deltaTime;
        }

        if (Input::isKeyPressed("D"))
        {
            transform.position.x += 100 * deltaTime;
        }
    }
};