#include "Tetris.hpp"

void Tetris::start()
{
    setWidth(400);
    setHeight(800);
    setTitle("Tetris");

    Scene scene;
    setActiveScene(scene);

    Grid grid(10, 20);
    for (auto& column : grid.tiles)
    {
        for (auto& tile : column)
        {
            activeScene->objects.push_back(std::make_shared<Tile>(tile));
        }
    }
    mGrid = std::make_shared<Grid>(grid);

    spawnTetromino(Type::O);

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
    }

    mElapsedTime += deltaTime;

    if (Input::isKeyDown("A") && !checkForLeftCollision())
    {
        mCurrTetromino->moveLeft();
    }

    if (Input::isKeyDown("D") && !checkForRightCollision())
    {
        mCurrTetromino->moveRight();
    }

    for (auto tile : mCurrTetromino->tiles)
    {
        withinBoundsX(tile);
    }
    updateGrid();
}

void Tetris::tick()
{
    if (mCurrTetromino->getTransform()->position.y == getHeight() - (mCurrTetromino->getTransform()->scale.y) || checkForDownCollision())
    {
        for (auto& tile : mCurrTetromino->tiles)
        {
            mLockedTiles.push_back(std::make_shared<Tile>(tile));
            printf("%d, %d\n", tile.row, tile.column);
        }
        spawnTetromino(Type::I);
    }

    for (int i = 0; i < mGrid->numRows; i++)
    {
        if (mGrid->isRowFull(mGrid->values[i]))
        {
            printf("Row %d is full.\n", i);
        }
    }

    mCurrTetromino->moveDown();
    mElapsedTime = 0;
}


void Tetris::spawnTetromino(Type type)
{
    Tetromino tetromino(type);
    auto tet = std::make_shared<Tetromino>(tetromino);
    mCurrTetromino = tet;

    activeScene->objects.push_back(tet);

    for (auto& tile : tetromino.tiles)
    {
        activeScene->objects.push_back(std::make_shared<Tile>(tile));
    }

    updateGrid();
}

void Tetris::updateGrid()
{
    for (int i = 0; i < mGrid->numRows; i++)
    {
        for (int j = 0; j < mGrid->numColumns; j++)
        {
            mGrid->setValue(i,j,0);
            for (auto& tile : mCurrTetromino->tiles)
            {
                if (mGrid->tiles[i][j].getTransform()->position.x == tile.getTransform()->position.x && mGrid->tiles[i][j].getTransform()->position.y == tile.getTransform()->position.y)
                {
                    mGrid->setValue(i,j,1);
                    tile.row = i;
                    tile.column = j;
                }
            }

            for (auto& tile : mLockedTiles)
            {
                if (mGrid->tiles[i][j].getTransform()->position.x == tile->getTransform()->position.x && mGrid->tiles[i][j].getTransform()->position.y == tile->getTransform()->position.y)
                {
                    mGrid->setValue(i,j,2);
                    tile->row = i;
                    tile->column = j;
                }
            }
        }
    }
}

bool Tetris::checkForDownCollision()
{
    bool isCollided;
    for (auto& tile : mCurrTetromino->tiles)
    {
        if ((mGrid->getValue(tile.row + 1,tile.column) == 2))
        {
            printf("%d, %d\n",tile.row - 1,tile.column);
            printf("Collision detected.\n");
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
        if ((mGrid->getValue(tile.row,tile.column + 1) == 2))
        {
            printf("%d, %d\n",tile.row,tile.column + 1);
            printf("Collision detected.\n");
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
        if ((mGrid->getValue(tile.row,tile.column - 1) == 2))
        {
            printf("%d, %d\n",tile.row,tile.column - 1);
            printf("Collision detected.\n");
            return isCollided = true;
        }
    }
    return isCollided = false;
}

void Tetris::withinBoundsX(Tile tile)
{
    auto transform = tile.getTransform();
    if (transform->position.x + transform->scale.x > getWidth())
    {
        for (auto& t : mCurrTetromino->tiles)
        {
            t.getTransform()->position.x -= t.getTransform()->scale.x;
        }
        return;
    }

    if (transform->position.x < 0)
    {
        for (auto& t : mCurrTetromino->tiles)
        {
            t.getTransform()->position.x += t.getTransform()->scale.x;
        }
        return;
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