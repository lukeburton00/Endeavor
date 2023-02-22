#include "L.hpp"

void L::buildTiles()
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

        if (i == 0)
        {
            tileTransform->position.y -= getTransform()->scale.y;
            tileTransform->position.x += getTransform()->scale.x;
        }
        tileSprite->setColor(glm::vec4(0.0f,0.0f,1.0f,1.0f));

        if (i == 3)
        {
            getTransform()->position.y = tileTransform->position.y;
        }
        tiles[i] = tile;
    }
}

void L::resolveRotations()
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
    }
}   