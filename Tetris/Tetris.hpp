#pragma once
#include "Engine.hpp"
#include "Tetromino.hpp"
#include "Grid.hpp"

class Tetris : public Game
{
public:
    void start() override;
    void update(float deltaTime) override;
    void stop() override;

private:
    Time mTimer;
    float mElapsedTime;
    float mTickLength;
    std::shared_ptr<Tetromino> mCurrTetromino;
    std::shared_ptr<Grid> mGrid;
    std::vector<std::shared_ptr<Tile>> mLockedTiles;

    void tick();
    void updateGrid();
    void spawnTetromino();
    void clearTiles(int row);
    bool checkForDownCollision();
    bool checkForRightCollision();
    bool checkForLeftCollision();
    bool rowIsFull(int row);
    void checkBounds();

};