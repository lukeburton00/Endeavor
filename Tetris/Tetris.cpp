#include "Tetris.hpp"

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
    spawnTetromino();

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
            mLockedTiles.push_back(tile);
            printf("%d, %d\n", tile->row, tile->column);
        }
        spawnTetromino();
    }

    for (int i = 0; i < mGrid->numRows; i++)
    {
        if (mGrid->isRowFull(mGrid->values[i]))
        {
            for (int i = 0; i < mLockedTiles.size(); i++)
            {
                auto tile = mLockedTiles[i];
                if (tile->row == i)
                {
                    tile->removeSprite();
                    mLockedTiles.erase(std::remove(mLockedTiles.begin(), mLockedTiles.end(), tile));
                    i--;
                }
            }

            for (int j = 0; j < mGrid->numColumns; j++)
            {
                mGrid->setValue(i,j,0);
            }

            for (auto it = mLockedTiles.begin(); it != mLockedTiles.end(); it++)
            {
                auto tile = it->get();
                if (tile->row < i)
                {
                    tile->moveDown();
                }
            }
        }
    }

    mCurrTetromino->moveDown();
    mElapsedTime = 0;
}


void Tetris::spawnTetromino()
{
    Type random = static_cast<Type>(rand() % 4);
    Tetromino tetromino(random);
    auto tet = std::make_shared<Tetromino>(tetromino);
    mCurrTetromino = tet;

    activeScene->objects.push_back(tet);

    for (auto& tile : tetromino.tiles)
    {
        activeScene->objects.push_back(tile);
    }

    updateGrid();
}

void Tetris::updateGrid()
{
    for (int i = 0; i < mGrid->numRows; i++)
    {
        for (int j = 0; j < mGrid->numColumns; j++)
        {
			auto gridTileTransform = mGrid->tiles[i][j]->getTransform();
            mGrid->setValue(i,j,0);
            for (auto& tile : mCurrTetromino->tiles)
            {
				auto tetrominoTileTransform = tile->getTransform();
                if (gridTileTransform->position.x == tetrominoTileTransform->position.x && gridTileTransform->position.y == tetrominoTileTransform->position.y)
                {
                    mGrid->setValue(i,j,1);
                    tile->row = i;
                    tile->column = j;
                }
            }

            for (auto& tile : mLockedTiles)
            {
				auto lockedTileTransform = tile->getTransform();
                if (gridTileTransform->position.x == lockedTileTransform->position.x &&
					gridTileTransform->position.y == lockedTileTransform->position.y)
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
        if ((mGrid->getValue(tile->row + 1,tile->column) == 2))
        {
            printf("%d, %d\n",tile->row - 1,tile->column);
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
        if ((mGrid->getValue(tile->row,tile->column + 1) == 2))
        {
            printf("%d, %d\n",tile->row,tile->column + 1);
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
        if ((mGrid->getValue(tile->row,tile->column - 1) == 2))
        {
            printf("%d, %d\n",tile->row,tile->column - 1);
            printf("Collision detected.\n");
            return isCollided = true;
        }
    }
    return isCollided = false;
}

void Tetris::withinBoundsX(std::shared_ptr<Tile> tile)
{
    auto transform = tile->getTransform();
    if (transform->position.x + transform->scale.x > getWidth())
    {
        for (auto& t : mCurrTetromino->tiles)
        {
            t->getTransform()->position.x -= t->getTransform()->scale.x;
            return;
        }
    }

    if (transform->position.x < 0)
    {
        for (auto& t : mCurrTetromino->tiles)
        {
            t->getTransform()->position.x += t->getTransform()->scale.x;
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
