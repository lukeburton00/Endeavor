#pragma once

#include "Engine.hpp"

class PlayerOneController : public Behavior
{
public:
    using Behavior::Behavior;
    float movementSpeed;

    void start() override
    {
        movementSpeed = 250.0f;
    }

    void update(const float& deltaTime) override
    {
        auto &transform = self.getComponent<Transform>();

        if (Input::isKeyDown("W"))
        {
            transform.position.y -= movementSpeed * deltaTime;
        }

        if (Input::isKeyDown("S"))
        {
            transform.position.y += movementSpeed * deltaTime;
        }
    }
};