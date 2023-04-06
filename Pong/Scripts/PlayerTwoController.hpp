#pragma once

#include "Engine.hpp"

class PlayerTwoController : public Behavior
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

        if (Input::isKeyDown("Up"))
        {
            transform.position.y -= movementSpeed * deltaTime;
        }

        if (Input::isKeyDown("Down"))
        {
            transform.position.y += movementSpeed * deltaTime;
        }

    }
};