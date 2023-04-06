#pragma once

#include "Engine.hpp"

class CameraController : public Behavior
{
public:
    using Behavior::Behavior;

    void start() override
    {
        movementSpeed = 100.0f;
    }

    void update(const float& deltaTime) override
    {
        auto& transform = self.getComponent<Transform>();

        if (Input::isKeyDown("W"))
        {
            transform.position.y += movementSpeed * deltaTime;
        }

        if (Input::isKeyDown("A"))
        {
            transform.position.x -= movementSpeed * deltaTime;
        }

        if (Input::isKeyDown("S"))
        {
            transform.position.y -= movementSpeed * deltaTime;
        }

        if (Input::isKeyDown("D"))
        {
            transform.position.x += movementSpeed * deltaTime;
        }
    }

private:
    float movementSpeed;
};