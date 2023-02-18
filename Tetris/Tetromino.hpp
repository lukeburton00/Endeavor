#pragma once
#include "Engine.hpp"
#include <array>

class Tetromino : public GameObject
{
public:
    std::array<GameObject, 4> tiles;
    Tetromino();
    void moveDown();
    void updateTiles();
private:
};