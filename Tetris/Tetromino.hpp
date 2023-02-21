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
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void rotate();
    void undoRotation();
    
private:
    void buildTiles();
    void resolveRotations();
    Type mType;
    int rotationState;

};