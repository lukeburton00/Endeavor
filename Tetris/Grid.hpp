#pragma once
#include "Engine.hpp"

class Grid
{
public:
    int numColumns, numRows;
    std::vector<std::vector<GameObject>> tiles;


    Grid(int width, int height)
    {
        numColumns = width;
        numRows = height;
        tiles = std::vector<std::vector<GameObject>>(numColumns, std::vector<GameObject>(numRows));
        mValues = std::vector<std::vector<int>>(numColumns, std::vector<int>(numRows));


        for (int i = 0; i < tiles.size(); i++)
        {
            for (int j = 0; j < tiles[i].size(); j++)
            {
                GameObject tile;
                auto sprite = tile.addSprite();
                auto transform = tile.addTransform();

                transform->setScale(glm::vec2(40.0f, 40.0f));
                transform->setPosition(glm::vec2(i * transform->scale.x, j * transform->scale.y));

                sprite->setColor(glm::vec4(0.5f, 0.5f, 0.5f, 0.5f));

                tiles[i][j] = tile;
                mValues[i][j] = 0;
                printf("%d",mValues[i][j]);
            }
            printf("\n");
        }
    }

    int getValue(int i, int j)
    {
        return mValues[i][j];
    }

    void setValue(int i, int j, int value)
    {
        mValues[i][j] = value;
    }

private:
    std::vector<std::vector<int>> mValues;
};