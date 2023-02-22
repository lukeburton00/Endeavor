#include "Tetris.hpp"
#include <random>
void Tetris::start()
{
    setWidth(400);
    setHeight(800);
    setTitle("Tetris");

    Scene scene;
    setActiveScene(scene);

    auto grid = std::make_shared<Grid>(10,20);
    for (auto& column : grid->tiles)
    {
        for (auto& tile : column)
        {
            activeScene->objects.push_back(tile);
        }
    }

    mGrid = grid;

    auto factory = std::make_shared<TetrominoFactory>();
    mFactory = factory;
    spawnTetromino(SDL_GetTicks64());
    mCurrTetromino->moveDown();
    updateGrid();

    mLockedTiles = std::vector<std::shared_ptr<Tile>>();

    mElapsedTime = 0;
    mTickLength = 1;
}

void Tetris::update(float deltaTime)
{
    if (Input::isKeyPressed("S"))
    {
        mTickLength = 0.1f;
    }

    else
    {
        mTickLength = 1.0f;
    }

    if (mElapsedTime >= mTickLength)
    {
        tick();
        updateGrid();
    }

    mElapsedTime += deltaTime;

    if (Input::isKeyDown("W"))
    {
        mCurrTetromino->rotate();
        for (auto& tetTile : mCurrTetromino->tiles)
        {
            auto tetTileTransform = tetTile->getTransform();

            if (tetTileTransform->position.x >= getWidth())
            {
                mCurrTetromino->moveLeft();
            }

            if (tetTileTransform->position.x < 0)
            {
                mCurrTetromino->moveRight();
            }

            if (tetTileTransform->position.y >= getHeight())
            {
                mCurrTetromino->undoRotation();
            }
            
            for (auto& lockedTile : mLockedTiles)
            {
                auto lockedTileTransform = lockedTile->getTransform();
                if ((lockedTileTransform->position == tetTileTransform->position))
                {
                    mCurrTetromino->undoRotation();
                    return;
                }
            }
        }
        updateGrid();
    }

    if (Input::isKeyDown("A") && !checkForLeftCollision())
    {
        mCurrTetromino->moveLeft();
        updateGrid();
    }

    if (Input::isKeyDown("D") && !checkForRightCollision())
    {
        mCurrTetromino->moveRight();
        updateGrid();
    }
}

void Tetris::tick()
{
    bool hitBottom = checkForDownCollision();
    if (hitBottom)
    {
        for (auto& tile : mCurrTetromino->tiles)
        {
            mLockedTiles.push_back(tile);
        }
        spawnTetromino(SDL_GetTicks64());
    }

    mCurrTetromino->moveDown();

    mElapsedTime = 0;
}


void Tetris::spawnTetromino(int seed)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 6);
    int rand = distr(gen);
    printf("%d\n", rand);

    Type randomType = static_cast<Type>(rand);
    auto tetromino = mFactory->getTetromino(randomType);
    tetromino->buildTiles();

    mCurrTetromino = tetromino;
    activeScene->objects.push_back(tetromino);

    for (auto& tile : tetromino->tiles)
    {
        activeScene->objects.push_back(tile);
    }
}

void Tetris::updateGrid()
{
    for (int i = 0; i < mGrid->numRows; i++)
    {
        for (int j = 0; j < mGrid->numColumns; j++)
        {
            mGrid->setValue(i,j,0);
			auto gridTileTransform = mGrid->tiles[i][j]->getTransform();

            for (auto& tile : mCurrTetromino->tiles)
            {
                if (tile->getTransform()->position.x == gridTileTransform->position.x 
                && tile->getTransform()->position.y == gridTileTransform->position.y)
                {
                    tile->row = i;
                    tile->column = j;
                    mGrid->setValue(i,j,1);
                }
            }

            for (auto& tile : mLockedTiles)
            {
				auto lockedTileTransform = tile->getTransform();

                if (gridTileTransform->position.x == lockedTileTransform->position.x 
                && gridTileTransform->position.y == lockedTileTransform->position.y)
                {
                    tile->row = i;
                    tile->column = j;
                    mGrid->setValue(i,j,2);
                }
            }
        }
    }
    for (int i = 0; i < mGrid->numRows; i++)
    {
        if (rowIsFull(i))
        {
            clearTiles(i);
            moveStaticTilesDown(i);
        }
    }
}

bool Tetris::rowIsFull(int row)
{
    if (mGrid->isRowFull(mGrid->values[row]))
    {
        return true;
    }
    return false;
}

void Tetris::clearTiles(int row)
{
    printf("Clearing tiles on row %d\n", row);
    for (auto it = mLockedTiles.begin(); it < mLockedTiles.end(); it++)
    {
        auto tile = it->get();
        if (tile->row == row)
        {
            tile->removeSprite();
            mLockedTiles.erase(it--);
        }
    }

    for (int j = 0; j < mGrid->numColumns; j++)
    {
        mGrid->setValue(row,j,0);
    }
}

void Tetris::moveStaticTilesDown(int row)
{
    for (auto tile : mLockedTiles)
    {
        if (tile->row < row)
        {
            tile->moveDown();
        }
    }
}

bool Tetris::checkForDownCollision()
{
    bool isCollided;
    for (auto& tile : mCurrTetromino->tiles)
    {
        if (tile->row < mGrid->numRows - 1 && (mGrid->getValue(tile->row + 1,tile->column) == 2))
        {
            return isCollided = true;
        }

        if (tile->row == mGrid->numRows - 1)
        {
            return isCollided = true;
        }
    }
    return isCollided = false;
}

bool Tetris::checkForRightCollision()
{
    bool isCollided;
    for (auto& tile : mCurrTetromino->tiles)
    {
        if (tile->column < mGrid->numColumns - 1 && (mGrid->getValue(tile->row,tile->column + 1) == 2))
        {
            return isCollided = true;
        }

        if (tile->column == mGrid->numColumns - 1)
        {
            return isCollided = true;
        }
    }
    return isCollided = false;
}

bool Tetris::checkForLeftCollision()
{
    bool isCollided;
    for (auto& tile : mCurrTetromino->tiles)
    {
        if (tile->column > 0 && (mGrid->getValue(tile->row,tile->column - 1) == 2))
        {
            printf("%d, %d\n",tile->row,tile->column - 1);
            printf("Collision detected.\n");
            return isCollided = true;
        }

        if (tile->column == 0)
        {
            return isCollided = true;
        }
    }
    return isCollided = false;
}

void Tetris::stop()
{

}

int main() 
{
    Tetris game;
    Application engine(game);
    engine.start();
    return 0;
}
