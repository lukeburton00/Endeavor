#pragma once
#include "Engine.hpp"

class Grid : public Behavior
{
    using Behavior::Behavior;

    std::vector<Entity> tiles;
    int gridWidth, gridHeight;
    
    void start() override
    {
        gridWidth = 100;
        gridHeight = 100;

        for (int i = 0; i < gridWidth; i++)
        {
            for (int j = 0; j < gridHeight; j++)
            {
                glm::vec3 scale = glm::vec3(5.0f, 5.0f, 1.0f);
                glm::vec3 position = glm::vec3(i * scale.x, j * scale.y, 0.0f);
                auto tile = mScene->createEntity();

                mScene->addComponent<Transform>(tile, position, scale);
                mScene->addComponent<Sprite>(tile);
                
                tiles.push_back(tile);
            }
        }
    }

    void update(float deltaTime) override
    {
        if (Input::isLeftMouseButtonPressed())
        {
            printf("Left mouse button pressed\n");
        }

        if (Input::isRightMouseButtonPressed())
        {
            printf("Right mouse button pressed\n");
        }

        if (Input::isLeftMouseButtonDown())
        {
            printf("Left mouse button down\n");
        }

        if (Input::isRightMouseButtonDown())
        {
            printf("Right mouse button down\n");
        }
    }
};