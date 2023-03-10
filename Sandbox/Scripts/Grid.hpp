#pragma once
#include "Engine.hpp"

enum class State 
{
    CREATE,
    PLAY
};

class Grid : public Behavior
{
    using Behavior::Behavior;

    std::vector<std::vector<Entity> > tiles;
    std::vector<std::vector<Entity> > nextTiles;
    int gridWidth, gridHeight;

    State state;
    float elapsedTime;
    float tickSpeed;
    
    void start() override
    {
        gridWidth = 200;
        gridHeight = 200;

        tiles = std::vector<std::vector<Entity> >(gridWidth, std::vector<Entity>(gridHeight));
        nextTiles = std::vector<std::vector<Entity> >(gridWidth, std::vector<Entity>(gridHeight));


        for (int i = 0; i < gridWidth; i++)
        {
            for (int j = 0; j < gridHeight; j++)
            {
                glm::vec3 scale = glm::vec3(5.0f, 4.0f, 1.0f);
                glm::vec3 position = glm::vec3(i * scale.x, j * scale.y, 0.0f);

                auto tile = mScene->createEntity();

                mScene->addComponent<Transform>(tile, position, scale);
                mScene->addComponent<Sprite>(tile, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "GridTexture");

                tiles[i][j] = tile;

                tile = mScene->createEntity();
                mScene->addComponent<Sprite>(tile, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "GridTexture");
                
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
                        auto transform = mScene->getRegistry()->get<Transform>(tiles[i][j]);

                        if ((mousePosition.x >= transform.position.x && mousePosition.x < (transform.position.x + transform.scale.x)) && (mousePosition.y >= transform.position.y && mousePosition.y < (transform.position.y + transform.scale.y)))
                        {
                            mScene->addComponent<Sprite>(tiles[i][j], glm::vec4(0.0f,1.0f,0.0f,1.0f), "TileTexture");
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
                        mScene->addComponent<Sprite>(nextTiles[i][j], mScene->getRegistry()->get<Sprite>(tiles[i][j]).color, mScene->getRegistry()->get<Sprite>(tiles[i][j]).textureTag);
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
                                if (mScene->getRegistry()->get<Sprite>(tile).textureTag == "TileTexture")
                                {
                                    numLivingNeighbors++;
                                }
                            }

                            neighbors.clear();

                            if ((mScene->getRegistry()->get<Sprite>(thisTile).textureTag == "TileTexture") && ((numLivingNeighbors == 3) || (numLivingNeighbors == 2)))
                            {
                                mScene->addComponent<Sprite>(nextTiles[i][j], glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), "TileTexture");
                            }

                            else if ((mScene->getRegistry()->get<Sprite>(thisTile).textureTag == "GridTexture") && (numLivingNeighbors == 3))
                            {
                                mScene->addComponent<Sprite>(nextTiles[i][j], glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), "TileTexture");
                            }

                            else 
                            {
                                mScene->addComponent<Sprite>(nextTiles[i][j], glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "GridTexture");
                            }
                        }
                    }
                }
                for (int i = 0; i < gridWidth; i++)
                {
                    for (int j = 0; j < gridHeight; j++)
                    {
                        mScene->addComponent<Sprite>(tiles[i][j], mScene->getRegistry()->get<Sprite>(nextTiles[i][j]).color, mScene->getRegistry()->get<Sprite>(nextTiles[i][j]).textureTag);
                    }
                }
                elapsedTime = 0.0f;
            }

            if (Input::isKeyPressed("W"))
            {
                tickSpeed -= 0.1f;
                if (tickSpeed < 0)
                {
                    tickSpeed = 0;
                }
            }

            if (Input::isKeyPressed("S"))
            {
                tickSpeed += 0.1f;
            }
        }
    }

    void reset()
    {
        state = State::CREATE;
        for (int i = 0; i < gridWidth; i++)
        {
            for (int j = 0; j < gridHeight; j++)
            {
                mScene->addComponent<Sprite>(tiles[i][j], glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "GridTexture");
            }
        }
    }
};