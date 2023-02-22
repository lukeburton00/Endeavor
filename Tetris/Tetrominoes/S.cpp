#include "S.hpp"

void S::buildTiles()
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

        if (i == 2 || i == 3)
        {
            tileTransform->position.y += tileTransform->scale.x;
            tileTransform->position.x -= tileTransform->scale.x * 3;
        }

        tileTransform->position.x += tileTransform->scale.x * 2;
        tileSprite->setColor(glm::vec4(0.0f,1.0f,0.0f,1.0f));

        if (i == 3)
        {
            getTransform()->position.y = tileTransform->position.y;
        }
        tiles[i] = tile;
    }
}

void S::resolveRotations()
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
    }
}