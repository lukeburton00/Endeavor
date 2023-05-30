#pragma once

#include "endeavor.hpp"

class Player
{
public:
    glm::vec2 position;
    glm::vec2 scale;
    glm::vec4 color;

    float moveSpeed;

    Player() : position(glm::vec2(0,0)), scale(glm::vec2(100,100)), color(glm::vec4(1,1,1,1)){}

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

    void draw(Endeavor::SpriteBatch& batch)
    {
        batch.drawSubTexture(position, scale, color, "dungeon_sheet", glm::vec2(0,2), glm::vec2(16,16), "default_shader");
    }
};