#include "Tetromino.hpp"

Tetromino::Tetromino(Type type)
{
    mType = type;
    auto transform = addTransform();

    transform->setScale(glm::vec2(40.0f, 40.0f));
    transform->setPosition(glm::vec2(120, 0));

    tiles = std::array<std::shared_ptr<Tile>, 4>();
    buildTiles();
    rotationState = 0;
}

void Tetromino::moveUp()
{
    auto transform = getTransform();
    transform->position.y -= transform->scale.x;
    for (auto& tile : tiles)
    {
        tile->moveUp();
    }
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
    auto transform = getTransform();
    transform->position.x -= transform->scale.x;
    for (auto tile : tiles)
    {
        auto tileTransform = tile->getTransform();
        tileTransform->position.x -= tileTransform->scale.x;
        tile->column--;
    }
}

void Tetromino::moveRight()
{
    auto transform = getTransform();
    transform->position.x += transform->scale.x;
    for (auto tile : tiles)
    {
        auto tileTransform = tile->getTransform();
        tileTransform->position.x += tileTransform->scale.x;
        tile->column++;
    }
}

void Tetromino::rotate()
{
    rotationState++;
    if (rotationState == 4)
    {
        rotationState = 0;
    }

    resolveRotations();

}

void Tetromino::undoRotation()
{
    rotationState--;
    if (rotationState < 0)
    {
        rotationState = 3;
    }

    resolveRotations();
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

                tileSprite->setColor(glm::vec4(1.0f,0.0f,0.0f,1.0f));
                break;
            }
                default:
                break;
        }
        if (i == 3)
        {
            getTransform()->position.y = tileTransform->position.y;
        }
        tiles[i] = tile;
    }
}



void Tetromino::resolveRotations()
{
    printf("Tetromino rotation state: %d\n", rotationState);
    printf("Tetromino type: %d\n", mType);

    for (int i = 0; i < tiles.size(); i++)
    {
        auto tetTransform = getTransform();
        auto tile = tiles[i];
        auto tileTransform = tile->getTransform();
        auto tileSprite = tile->getSprite();

        tileTransform->setPosition(tetTransform->position);

        switch (mType)
        {
            case Type::I:
            {
                switch (rotationState)
                {
                    case 0: case 2:
                    {
                        if (i == 0)
                        {
                            tetTransform->setPosition(tileTransform->position);
                        }

                        tileTransform->position.x += tileTransform->scale.x * i;
                        break;
                    }
                    case 1: case 3:
                    {
                        if (i == 0)
                        {
                            tetTransform->setPosition(tileTransform->position);
                        }

                        tileTransform->position.y += tileTransform->scale.y * i;
                        tileTransform->position.x += tileTransform->scale.x;

                        break;
                    }

                    default: break;
                }

                break;
             }

            case Type::J:
            {
                switch (rotationState)
                {
                    case 0:
                    {
                        tileTransform->position.x += tileTransform->scale.x * i;
                        if (i == 3)
                        {
                            tileTransform->position.y -= getTransform()->scale.y;
                            tileTransform->position.x -= getTransform()->scale.x;
                        }
                        break;
                    }

                    case 1:
                    {
                        if (i == 0)
                        {
                            tileTransform->position.x += tileTransform->scale.x;
                        }
                        if (i > 1)
                        {
                            tileTransform->position.y -= getTransform()->scale.y * (i - 1);
                        }
                        break;
                    }

                    case 2:
                    {
                        if (i > 0)
                        {
                            tileTransform->position.y -= getTransform()->scale.y;
                            tileTransform->position.x += getTransform()->scale.x * (i - 1);
                        }

                        break;
                    }

                    case 3:
                    {
                        if (i != 0)
                        {
                            tileTransform->position.x += tileTransform->scale.x;
                        }

                        if (i > 1)
                        {
                            tileTransform->position.y += tileTransform->scale.y * (i - 1);
                        }
                        break;
                        tileTransform->position.y += tileTransform->scale.y;

                    }

                    default: break;
                }
                break;
            }

            case Type::L:
            {
                switch (rotationState)
                {
                    case 0:
                    {
                        tileTransform->position.x += tileTransform->scale.x * i;
                        if (i == 0)
                        {
                            tileTransform->position.y -= getTransform()->scale.y;
                            tileTransform->position.x += getTransform()->scale.x;

                        }
                        break;
                    }

                    case 1:
                    {
                        if (i == 0)
                        {
                            tileTransform->position.x += getTransform()->scale.x;
                        }

                        else
                        {
                            tileTransform->position.y += tileTransform->scale.y * (i - 1);
                        }

                        tileTransform->position.y -= getTransform()->scale.y * 2;
                        tileTransform->position.x += getTransform()->scale.x;
                        break;
                    }

                    case 2:
                    {
                        if (i < 3)
                        {
                            tileTransform->position.x += getTransform()->scale.x * i;
                        }

                        else
                        {
                            tileTransform->position.x += getTransform()->scale.x * (i - 1);
                            tileTransform->position.y += getTransform()->scale.y;

                        }
                        tileTransform->position.y -= getTransform()->scale.y * 2;
                        break;
                    }

                    case 3:
                    {
                        if (i != 0)
                        {
                            tileTransform->position.x += tileTransform->scale.x;
                        }

                        if (i > 1)
                        {
                            tileTransform->position.y -= tileTransform->scale.y * (i - 1);
                        }
                        tileTransform->position.x += getTransform()->scale.x;
                        break;
                    }

                    default: break;
                }
                break;
            }

            case Type::O:
            {
                tileTransform->position.x += tileTransform->scale.x * i;
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
                break;
            }
            
            case Type::S:
            {
                switch (rotationState)
                {
                    case 0: 
                    {
                        tileTransform->position.x += tileTransform->scale.x * i;
                        if (i == 2 || i == 3)
                        {
                            tileTransform->position.y += tileTransform->scale.x;
                            tileTransform->position.x -= tileTransform->scale.x * 3;
                        }

                        tileTransform->position.x += tileTransform->scale.x * 2;
                        tileTransform->position.y += tileTransform->scale.y;
                        break;
                    }

                    case 1: 
                    {
                        tileTransform->position.y += tileTransform->scale.y * i;
                        if (i == 2 || i == 3)
                        {
                            tileTransform->position.y -= tileTransform->scale.y;
                            tileTransform->position.x += tileTransform->scale.x;
                        }
                        tileTransform->position.x += tileTransform->scale.x;
                        break;
                    }
                    
                    case 2:
                    {
                        tileTransform->position.x += tileTransform->scale.x * i;
                        if (i == 2 || i == 3)
                        {
                            tileTransform->position.y += tileTransform->scale.x;
                            tileTransform->position.x -= tileTransform->scale.x * 3;
                        }

                        tileTransform->position.x += tileTransform->scale.x * 2;
                        tileTransform->position.y -= getTransform()->scale.y;
                        break;
                    }

                    case 3:
                    {
                        tileTransform->position.y += tileTransform->scale.y * i;
                        if (i == 2 || i == 3)
                        {
                            tileTransform->position.y -= tileTransform->scale.y;
                            tileTransform->position.x += tileTransform->scale.x;
                        }

                        tileTransform->position.x += getTransform()->scale.x * 2;
                        break;
                    }

                    default: break;
                }
                break;
            }

            case Type::T:
            {
                switch (rotationState)
                {
                    case 0:
                    {
                        tileTransform->position.x += getTransform()->scale.x * i;
                        if (i == 0)
                        {
                            tileTransform->position.y -= tileTransform->scale.y;
                            tileTransform->position.x += tileTransform->scale.x * 2;
                        }
                        break;
                    }

                    case 1:
                    {
                        tileTransform->position.y += getTransform()->scale.y * i;
                        if (i == 0)
                        {
                            tileTransform->position.y += tileTransform->scale.y * 2;
                            tileTransform->position.x += tileTransform->scale.x;
                        }

                        tileTransform->position.y -= getTransform()->scale.y * 2;
                        tileTransform->position.x += getTransform()->scale.x * 2;

                        break;
                    }

                    case 2:
                    {
                        tileTransform->position.x += getTransform()->scale.x * i;
                        if (i == 0)
                        {
                            tileTransform->position.y += tileTransform->scale.y;
                            tileTransform->position.x += tileTransform->scale.x * 2;
                        }

                        break;
                    }

                    case 3:
                    {
                        tileTransform->position.y += getTransform()->scale.y * i;
                        if (i == 0)
                        {
                            tileTransform->position.y += tileTransform->scale.y * 2;
                            tileTransform->position.x -= tileTransform->scale.x;
                        }

                        tileTransform->position.y -= getTransform()->scale.y * 2;
                        tileTransform->position.x += getTransform()->scale.x * 2;

                        break;
                    }
                    default: break;
                }
                break;
            }

            case Type::Z:
            {
                switch (rotationState)
                {
                    case 0: 
                    {
                        tileTransform->position.x += tileTransform->scale.x * i;
                        if (i == 2 || i == 3)
                        {
                            tileTransform->position.y -= tileTransform->scale.x;
                            tileTransform->position.x -= tileTransform->scale.x * 3;
                        }
                        tileTransform->position.y += getTransform()->scale.y;
                        tileTransform->position.x += tileTransform->scale.x * 2;
                        break;
                    }

                    case 1: 
                    {
                        tileTransform->position.y -= tileTransform->scale.y * i;
                        if (i == 2 || i == 3)
                        {
                            tileTransform->position.y += tileTransform->scale.y;
                            tileTransform->position.x += tileTransform->scale.x;
                        }
                        tileTransform->position.x += tileTransform->scale.x;

                        break;
                    }

                    case 2:
                    {
                        tileTransform->position.x += tileTransform->scale.x * i;
                        if (i == 2 || i == 3)
                        {
                            tileTransform->position.y -= tileTransform->scale.x;
                            tileTransform->position.x -= tileTransform->scale.x * 3;
                        }

                        tileTransform->position.x += tileTransform->scale.x * 2;
                        tileTransform->position.y -= getTransform()->scale.y;

                        break;
                    }

                    case 3:
                    {
                        tileTransform->position.y -= tileTransform->scale.y * i;
                        if (i == 2 || i == 3)
                        {
                            tileTransform->position.y += tileTransform->scale.y;
                            tileTransform->position.x += tileTransform->scale.x;
                        }
                        tileTransform->position.x += getTransform()->scale.x * 2;
                        break;
                    }

                    default: break;
                }
                break;
            }
            default: break;
        }
    }
}