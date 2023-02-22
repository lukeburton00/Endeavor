#pragma once
#include "Engine.hpp"
#include "TetrominoFactory.hpp"
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
    std::shared_ptr<TetrominoFactory> mFactory;
    std::vector<std::shared_ptr<Tile>> mLockedTiles;

    void tick();
    void updateGrid();
    void spawnTetromino(int seed);
    void clearTiles(int row);
    void moveStaticTilesDown(int row);
    bool checkForDownCollision();
    bool checkForRightCollision();
    bool checkForLeftCollision();
    bool rowIsFull(int row);
};