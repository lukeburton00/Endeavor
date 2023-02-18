#include "Tetromino.hpp"

Tetromino::Tetromino()
{
    auto tetrominoTransform = addTransform();

    tetrominoTransform->setScale(glm::vec2(40.0f, 40.0f));
    tetrominoTransform->setPosition(glm::vec2(120, 0));

    for (int i = 0; i < tiles.size(); i++)
    {
        GameObject tile;
        tile.id = i;
        auto tileTransform = tile.addTransform();
        auto tileSprite = tile.addSprite();

        tileTransform->setPosition(tetrominoTransform->position);
        tileTransform->setScale(tetrominoTransform->scale);
        tileTransform->position.x += tileTransform->scale.x * i;

        tileSprite->setColor(glm::vec4(0.0f,0.5f,1.0f,1.0f));
        tiles[i] = tile;
    }
}

void Tetromino::moveDown()
{
    getTransform()->position.y += getTransform()->scale.x;
}

void Tetromino::updateTiles()
{
    for (auto& tile : tiles)
    {
        tile.getTransform()->position.y += getTransform()->scale.x;
    }
}