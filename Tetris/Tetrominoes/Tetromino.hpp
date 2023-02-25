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
    
    Tetromino(float scale);
    virtual void buildTiles() = 0;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void rotate();
    void undoRotation();

protected:
    virtual void resolveRotations() = 0;
    Type mType;
    int rotationState;
};