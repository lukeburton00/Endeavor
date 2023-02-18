#include "Tetris.hpp"


void Tetris::start()
{
    setWidth(400);
    setHeight(800);
    setTitle("Tetris");

    Scene scene;

    Grid grid(10, 20);
    for (int i = 0; i < grid.tiles.size(); i++)
    {
        for (int j = 0; j < grid.tiles[i].size(); j++)
        {
            scene.objects.push_back(std::make_shared<GameObject>(grid.tiles[i][j]));
        }
    }

    Tetromino tetromino;
    auto tet = std::make_shared<Tetromino>(tetromino);
    mCurrTetromino = tet;
    scene.objects.push_back(tet);

    for (auto& tile : tetromino.tiles)
    {
        scene.objects.push_back(std::make_shared<GameObject>(tile));
    }

    mGrid = std::make_shared<Grid>(grid);

    setActiveScene(scene);
    mElapsedTime = 0;
    mTickLength = 1;
}

void Tetris::update(float deltaTime)
{
    moveTetromino(deltaTime);
}

void Tetris::moveTetromino(float deltaTime)
{
    auto tetTransform = mCurrTetromino->getTransform();
    if (mElapsedTime >= mTickLength && tetTransform->position.y < 800 - tetTransform->scale.x)
    {
        mCurrTetromino->moveDown();
        mCurrTetromino->updateTiles();

        for (int i = 0; i < mGrid->numColumns; i++)
        {
            for (int j = 0; j < mGrid->numRows; j++)
            {
                mGrid->setValue(i,j,0);
                for (auto tile : mCurrTetromino->tiles)
                {
                    if (mGrid->tiles[i][j].getTransform()->position.x == tile.getTransform()->position.x && mGrid->tiles[i][j].getTransform()->position.y == tile.getTransform()->position.y)
                    {
                        mGrid->setValue(i,j,1);
                        mGrid->tiles[i][j+1].getSprite()->setColor(glm::vec4(1.0f,1.0f,1.0f,1.0f));
                    }
                }
                printf("%d",mGrid->getValue(i,j));
            }
            printf("\n");
        }
        mElapsedTime = 0;
    }

    mElapsedTime += deltaTime;
    if (Input::isKeyDown("A"))
    {
        for (auto tile : mCurrTetromino->tiles)
        {
            auto tileTransform = tile.getTransform();
            tileTransform->position.x -= tileTransform->scale.x;
        }
    }

    if (Input::isKeyDown("D"))
    {
        for (auto tile : mCurrTetromino->tiles)
        {
            auto tileTransform = tile.getTransform();
            tileTransform->position.x += tileTransform->scale.x;

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