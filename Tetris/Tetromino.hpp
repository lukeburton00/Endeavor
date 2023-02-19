#pragma once
#include "Engine.hpp"
#include "Tile.hpp"
#include <array>

enum class Type
{
    I,
    J,
    L,
    O,
    S,
    T,
    Z
};

class Tetromino : public GameObject
{
public:
    std::array<std::shared_ptr<Tile>, 4> tiles;
    Tetromino(Type type);
    void moveDown();
    void moveLeft();
    void moveRight();
    
private:
    void buildTiles();
    Type mType;
};