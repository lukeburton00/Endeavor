#include "Tetromino.hpp"

Tetromino::Tetromino(Type type)
{
    mType = type;
    auto transform = addTransform();

    transform->setScale(glm::vec2(40.0f, 40.0f));
    transform->setPosition(glm::vec2(120, 0));

    buildTiles();
}

void Tetromino::moveDown()
{
    auto transform = getTransform();
    transform->position.y += transform->scale.x;
    for (auto& tile : tiles)
    {
        tile->getTransform()->position.y += transform->scale.x;
    }
}

void Tetromino::moveLeft()
{
    for (auto tile : tiles)
    {
        auto transform = tile->getTransform();
        transform->position.x -= transform->scale.x;
        tile->column -=1;
    }
}

void Tetromino::moveRight()
{
    for (auto tile : tiles)
    {
        auto transform = tile->getTransform();
        transform->position.x += transform->scale.x;
        tile->column +=1;
    }
}

void Tetromino::buildTiles()
{
    switch(mType)
    {
        case Type::I:
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
                tileSprite->setColor(glm::vec4(0.0f,0.5f,1.0f,1.0f));
                tiles[i] = tile;
            }
            break;
        }

        case Type::J:
        {
            for (int i = 0; i < tiles.size(); i++)
            {
                auto tile = std::make_shared<Tile>();
                tile->id = i;
                auto tileTransform = tile->addTransform();
                auto tileSprite = tile->addSprite();

                tileTransform->setPosition(getTransform()->position);
                tileTransform->setScale(getTransform()->scale);

                if (i == 1)
                {
                    tileTransform->position.y -= getTransform()->scale.y;
                }

                if (i > 1)
                {
                    tileTransform->position.x += getTransform()->scale.x * (i - 1);
                    tileTransform->position.y -= getTransform()->scale.y;
                }
                tileSprite->setColor(glm::vec4(0.0f,0.0f,1.0f,1.0f));
                tiles[i] = tile;
            }
            break;
        }

        case Type::L:
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

                tileSprite->setColor(glm::vec4(0.0f,0.5f,1.0f,1.0f));
                tiles[i] = tile;
            }
            break;
        }

        case Type::O:
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

                if (i >= 2)
                {
                    tileTransform->position.x -= tileTransform->scale.x * 2;
                    tileTransform->position.y += tileTransform->scale.y;
                }

                if (i == 3)
                {
                    getTransform()->position.y = tileTransform->position.y;
                }

                tileSprite->setColor(glm::vec4(1.0f,1.0f,0.0f,1.0f));
                tiles[i] = tile;
            }
            break;

        }

        case Type::S:
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

                tileSprite->setColor(glm::vec4(0.0f,0.5f,1.0f,1.0f));
                tiles[i] = tile;
            }
            break;

        }

        case Type::T:
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

                tileSprite->setColor(glm::vec4(0.0f,0.5f,1.0f,1.0f));
                tiles[i] = tile;
            }
            break;

        }

        case Type::Z:
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

                tileSprite->setColor(glm::vec4(0.0f,0.5f,1.0f,1.0f));
                tiles[i] = tile;
            }
            break;
        }

        default: break;
    }
}