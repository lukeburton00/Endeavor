#pragma once

#include "Engine.hpp"

using namespace Endeavor;

class Grid : public Behavior
{

enum class State 
{
    CREATE,
    PLAY
};

public:
    using Behavior::Behavior;

    std::vector<std::vector<Entity> > tiles;
    std::vector<std::vector<Entity> > nextTiles;
    int gridWidth, gridHeight;

    State state;
    float elapsedTime;
    float tickSpeed;
    
    void start() override
    {
        gridWidth = 150;
        gridHeight = 150;

        tiles = std::vector<std::vector<Entity> >(gridWidth, std::vector<Entity>(gridHeight));
        nextTiles = std::vector<std::vector<Entity> >(gridWidth, std::vector<Entity>(gridHeight));


        for (int i = 0; i < gridWidth; i++)
        {
            for (int j = 0; j < gridHeight; j++)
            {
                glm::vec3 scale = glm::vec3(5.0f, 5.0f, 1.0f);
                glm::vec3 position = glm::vec3(i * scale.x, j * scale.y, 0.0f);

                auto tile = mScene->createEntity("Tile");

                tile.addComponent<Transform>(position, scale);
                tile.addComponent<Sprite>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "GridTexture");

                tiles[i][j] = tile;

                tile = mScene->createEntity("Tile");
                tile.addComponent<Sprite>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "GridTexture");
                
                nextTiles[i][j] = tile;
            }
        }

        state = State::CREATE;
        tickSpeed = 0.5f;
        elapsedTime = 0.0f;
    }

    void update(const float& deltaTime) override
    {
        elapsedTime += deltaTime;
        glm::vec2 mousePosition = glm::vec2(Input::mousePositionX, Input::mousePositionY);

        if (Input::isKeyPressed("R"))
        {
            reset();
        }

        if (state == State::CREATE)
        {
            if (Input::isKeyPressed("Space"))
            {
                state = State::PLAY;
                return;
            }

            if (Input::isLeftMouseButtonDown())
            {

                for (int i = 0; i < gridWidth; i++)
                {
                    for (int j = 0; j < gridHeight; j++)
                    {
                        auto transform = tiles[i][j].getComponent<Transform>();

                        if ((mousePosition.x >= transform.position.x && mousePosition.x < (transform.position.x + transform.scale.x)) && (mousePosition.y >= transform.position.y && mousePosition.y < (transform.position.y + transform.scale.y)))
                        {
                            tiles[i][j].addComponent<Sprite>(glm::vec4(0.0f,1.0f,0.0f,1.0f), "TileTexture");
                        }
                    }
                }
            }
        }

        if (state == State::PLAY)
        {
            if (Input::isKeyPressed("Space"))
            {
                state = State::CREATE;
                return;
            }

            if (elapsedTime > tickSpeed)
            {
                for (int i = 0; i < gridWidth; i++)
                {
                    for (int j = 0; j < gridHeight; j++)
                    {
                        nextTiles[i][j].addComponent<Sprite>(tiles[i][j].getComponent<Sprite>().color, tiles[i][j].getComponent<Sprite>().textureTag);
                    }
                }

                for (int i = 0; i < gridWidth; i++)
                {
                    for (int j = 0; j < gridHeight; j++)
                    {
                        if ((i > 0 && j > 0) && (i < gridWidth - 1 && j < gridHeight - 1))
                        {
                            auto thisTile = tiles[i][j];
                            int numLivingNeighbors = 0;
                            std::vector<Entity> neighbors;

                            neighbors.push_back(tiles[i + 1][j]);
                            neighbors.push_back(tiles[i][j + 1]);
                            neighbors.push_back(tiles[i + 1][j + 1]);
                            neighbors.push_back(tiles[i - 1][j]);
                            neighbors.push_back(tiles[i][j - 1]);
                            neighbors.push_back(tiles[i - 1][j - 1]);
                            neighbors.push_back(tiles[i + 1][j - 1]);
                            neighbors.push_back(tiles[i - 1][j + 1]);

                            for (auto tile : neighbors)
                            {
                                if (tile.getComponent<Sprite>().textureTag == "TileTexture")
                                {
                                    numLivingNeighbors++;
                                }
                            }

                            neighbors.clear();

                            if ((thisTile.getComponent<Sprite>().textureTag == "TileTexture") && ((numLivingNeighbors == 3) || (numLivingNeighbors == 2)))
                            {
                                nextTiles[i][j].addComponent<Sprite>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), "TileTexture");
                            }

                            else if ((thisTile.getComponent<Sprite>().textureTag == "GridTexture") && (numLivingNeighbors == 3))
                            {
                                nextTiles[i][j].addComponent<Sprite>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), "TileTexture");
                            }

                            else 
                            {
                                nextTiles[i][j].addComponent<Sprite>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "GridTexture");
                            }
                        }
                    }
                }
                for (int i = 0; i < gridWidth; i++)
                {
                    for (int j = 0; j < gridHeight; j++)
                    {
                        tiles[i][j].addComponent<Sprite>(nextTiles[i][j].getComponent<Sprite>().color, nextTiles[i][j].getComponent<Sprite>().textureTag);
                    }
                }
                elapsedTime = 0.0f;
            }

            if (Input::isKeyPressed("I"))
            {
                tickSpeed -= 0.1f;
                if (tickSpeed < 0)
                {
                    tickSpeed = 0;
                }
            }

            if (Input::isKeyPressed("K"))
            {
                tickSpeed += 0.1f;
            }
        }
    }

private:
    void reset()
    {
        state = State::CREATE;
        for (int i = 0; i < gridWidth; i++)
        {
            for (int j = 0; j < gridHeight; j++)
            {
                tiles[i][j].addComponent<Sprite>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "GridTexture");
            }
        }
    }
};