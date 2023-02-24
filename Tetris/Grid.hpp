#pragma once
#include "Engine.hpp"
#include "Tile.hpp"

class Grid
{
public:
    int numColumns, numRows;
    float minPositionX, maxPositionX;
    float minPositionY, maxPositionY;

    std::vector<std::vector<std::shared_ptr<Tile>>> tiles;
    std::vector<std::vector<int>> values;

    Grid(int width, int height, float tileScale)
    {
        numColumns = width;
        numRows = height;
        tiles = std::vector<std::vector<std::shared_ptr<Tile>>>(numRows, std::vector<std::shared_ptr<Tile>>(numColumns));
        values = std::vector<std::vector<int>>(numRows, std::vector<int>(numColumns));

        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j < numColumns; j++)
            {
                auto tile = std::make_shared<Tile>();
                tile->row = i;
                tile->column = j;

                auto sprite = tile->addSprite();
                auto transform = tile->addTransform();

                transform->setScale(glm::vec2(tileScale, tileScale));
                transform->setPosition(glm::vec2(j * transform->scale.x, i * transform->scale.y));

                sprite->textureName = "GridTexture";
                sprite->setColor(glm::vec4(0.5f,0.5f, 0.5f, 1.0f));

                tiles[i][j] = tile;
                values[i][j] = 0;
            }
        }

        minPositionX = 0;
        minPositionY = 0;
        maxPositionX = (numColumns) * tileScale;
        maxPositionY = (numRows) * tileScale;
    }

    int getValue(int i, int j)
    {
        return values[i][j];
    }

    void setValue(int i, int j, int value)
    {
        values[i][j] = value;
    }

    bool isRowFull(std::vector<int> row)
    {
        for (auto cell : row)
        {
            if (cell != 2)
            return false;
        }
        return true;
    }
};