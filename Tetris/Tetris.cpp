#include "Tetris.hpp"

void Tetris::start()
{

    setTitle("Tetris");

    tileScale = 20.0f;

    setWidth(50 * tileScale);
    setHeight(50 * tileScale);

    Scene scene;
    setActiveScene(scene);

    auto grid = std::make_shared<Grid>(50,50, tileScale);
    for (auto& column : grid->tiles)
    {
        for (auto& tile : column)
        {
            tile->getSprite()->textureName = "GridTexture";
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
    totalRowsCleared = 0;
    currentLevel = 1;
}

void Tetris::update(float deltaTime)
{
    float finalTickLength = mTickLength;
    if (Input::isKeyDown("R"))
    {
        reset();
    }

    if (Input::isKeyPressed("S"))
    {
        finalTickLength = 0.05;
    }

    if (mElapsedTime >= finalTickLength)
    {
        tick();
        updateGrid();
    }

    mElapsedTime += deltaTime;

    if (Input::isKeyDown("W"))
    {
        mCurrTetromino->rotate();
        updateGrid();
        for (auto& tetTile : mCurrTetromino->tiles)
        {
            auto tetTileTransform = tetTile->getTransform();

            if (tetTileTransform->position.x >= mGrid->maxPositionX)
            {
                mCurrTetromino->moveLeft();
            }

            if (tetTileTransform->position.x < mGrid->minPositionX)
            {
                mCurrTetromino->moveRight();
            }

            if (tetTileTransform->position.y >= mGrid->maxPositionY)
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

    checkLoseCondition();
    mCurrTetromino->moveDown();
    mElapsedTime = 0;
}


void Tetris::spawnTetromino(int seed)
{

    Type randomType = static_cast<Type>(Random::randomIntInRange(0,6));

    while (randomType == previousType)
    {
        randomType = static_cast<Type>(Random::randomIntInRange(0,6));
    }

    auto tetromino = mFactory->getTetromino(randomType, tileScale);
    tetromino->buildTiles();

    mCurrTetromino = tetromino;
    activeScene->objects.push_back(tetromino);

    for (auto& tile : tetromino->tiles)
    {
        tile->getSprite()->textureName = "TileTexture";
        activeScene->objects.push_back(tile);
    }

    previousType = randomType;
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
            totalRowsCleared++;
            if (totalRowsCleared % 10 == 0)
            {
                levelUp();
            }
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
    for (int i = 0; i < mLockedTiles.size(); i++)
    {
        auto tile = mLockedTiles[i];
        if (tile->row == row)
        {
            tile->removeSprite();
            mLockedTiles.erase(std::remove(mLockedTiles.begin(), mLockedTiles.end(), tile));
            i--;
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

void Tetris::reset()
{
    printf("reset tetris\n");

    mLockedTiles.clear();
    activeScene->objects.clear();
    auto grid = std::make_shared<Grid>(20,30, tileScale);

    for (auto& row : mGrid->tiles)
    {
        for (auto& tile : row)
        {
            tile->getSprite()->textureName = "GridTexture";
            activeScene->objects.push_back(tile);
        }
    }
    spawnTetromino(SDL_GetTicks64());
    mCurrTetromino->moveDown();
}

void Tetris::levelUp()
{
    currentLevel++;
    if (currentLevel < 29)
    {
        mTickLength -= 0.1f;
    }
}

void Tetris::checkLoseCondition()
{
    for (auto& tile : mLockedTiles)
    {
        if (tile->row == 0)
        {
            reset();
            mTickLength = 1;
        }
    }
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