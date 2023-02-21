#include "Tetromino.hpp"

Tetromino::Tetromino(Type type)
{
    mType = type;
    auto transform = addTransform();

    transform->setScale(glm::vec2(40.0f, 40.0f));
    transform->setPosition(glm::vec2(120, 0));

    tiles = std::array<std::shared_ptr<Tile>, 4>();
    buildTiles();
}

void Tetromino::moveDown()
{
    auto transform = getTransform();
    transform->position.y += transform->scale.x;
    for (auto& tile : tiles)
    {
        tile->moveDown();
    }
}

void Tetromino::moveLeft()
{
    for (auto tile : tiles)
    {
        auto transform = tile->getTransform();
        transform->position.x -= transform->scale.x;
        tile->column--;
    }
}

void Tetromino::moveRight()
{
    for (auto tile : tiles)
    {
        auto transform = tile->getTransform();
        transform->position.x += transform->scale.x;
        tile->column++;
    }
}

void Tetromino::buildTiles()
{
    for (int i = 0; i < tiles.size(); i++)
    {
        auto tile = std::make_shared<Tile>();
        tile->id = i;
        auto tileTransform = tile->addTransform();
        auto tileSprite = tile->addSprite();
        tileTransform->setPosition(getTransform()->position);
        tileTransform->setScale(getTransform()->scale);
        tileTransform->position.x += getTransform()->scale.x * i;


        switch (mType)
        {
            case Type::I:
            {
                tileSprite->setColor(glm::vec4(0.0f,0.5f,1.0f,1.0f));
                break;
            }

            case Type::J:
            {
                if (i == 3)
                {
                    tileTransform->position.y -= getTransform()->scale.y;
                    tileTransform->position.x -= getTransform()->scale.x;
                }

                tileSprite->setColor(glm::vec4(1.0f,0.5f,0.0f,1.0f));
                break;
            }

            case Type::L:
            {
                if (i == 0)
                {
                    tileTransform->position.y -= getTransform()->scale.y;
                    tileTransform->position.x += getTransform()->scale.x;
                }
                tileSprite->setColor(glm::vec4(0.0f,0.0f,1.0f,1.0f));
                break;
            }

            case Type::O:
            {
                if (i == 0)
                {
                    tileTransform->position.x += tileTransform->scale.x;
                    tileTransform->position.y += tileTransform->scale.y;
                }

                if (i == 3)
                {
                    tileTransform->position.x -= tileTransform->scale.x;
                    tileTransform->position.y += tileTransform->scale.y;
                }

                tileSprite->setColor(glm::vec4(1.0f,1.0f,0.0f,1.0f));
                break;
            }
            
            case Type::S:
            {
                if (i == 2 || i == 3)
                {
                    tileTransform->position.y += tileTransform->scale.x;
                    tileTransform->position.x -= tileTransform->scale.x * 3;
                }

                tileTransform->position.x += tileTransform->scale.x * 2;
                tileSprite->setColor(glm::vec4(0.0f,1.0f,0.0f,1.0f));
                break;
            }

            case Type::T:
            {
                if (i == 0)
                {
                    tileTransform->position.y -= tileTransform->scale.y;
                    tileTransform->position.x += tileTransform->scale.x * 2;
                }
                tileSprite->setColor(glm::vec4(1.0f,0.0f,1.0f,1.0f));
                tiles[i] = tile;
                break;
            }

            case Type::Z:
            {
                if (i == 0 || i == 1)
                {
                    tileTransform->position.y -= tileTransform->scale.x;
                    tileTransform->position.x += tileTransform->scale.x;
                }

                tileSprite->setColor(glm::vec4(1.0f,0.0f,1.0f,1.0f));
                break;
            }
                default:
                break;
        }
        if (i == 3)
        {
            getTransform()->setPosition(tileTransform->position);
        }
        tiles[i] = tile;
    }
}