#include "I.hpp"

void I::buildTiles()
{
    for (int i = 0; i < tiles.size(); i++)
    {
        auto tile = std::make_shared<Tile>();
        tile->id = i;
        auto tileTransform = tile->addTransform();
        auto tileSprite = tile->addSprite();
        tileTransform->setPosition(glm::vec2(getTransform()->position.x, getTransform()->position.y - getTransform()->scale.y));
        tileTransform->setScale(getTransform()->scale);
        tileTransform->position.x += getTransform()->scale.x * i;
        tileSprite->setColor(glm::vec4(0.0f,0.5f,1.0f,1.0f));

        if (i == 3)
        {
            getTransform()->position.y = tileTransform->position.y;
        }
        tiles[i] = tile;
    }
}

void I::resolveRotations()
{
    for (int i = 0; i < tiles.size(); i++)
    {
        auto tetTransform = getTransform();
        auto tile = tiles[i];
        auto tileTransform = tile->getTransform();
        auto tileSprite = tile->getSprite();
        tileTransform->setPosition(tetTransform->position);
        
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
    }
}