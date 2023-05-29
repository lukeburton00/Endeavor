#pragma once

#include "endeavor.hpp"

class Player
{
public:
    glm::vec2 position;
    glm::vec2 scale;
    float moveSpeed;

    Player() : position(glm::vec2(0,0)), scale(glm::vec2(100,100)){}

    void update(float deltaTime)
    {
        if (Endeavor::Input::isKeyDown("W"))
        {
            position.y -= moveSpeed * deltaTime;
        }

        if (Endeavor::Input::isKeyDown("A"))
        {
            position.x -= moveSpeed * deltaTime;
        }

        if (Endeavor::Input::isKeyDown("S"))
        {
            position.y += moveSpeed * deltaTime;
        }

        if (Endeavor::Input::isKeyDown("D"))
        {
            position.x += moveSpeed * deltaTime;
        }
    }
};