#include "J.hpp"

void J::buildTiles()
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
        
        if (i == 3)
        {
            tileTransform->position.y -= getTransform()->scale.y;
            tileTransform->position.x -= getTransform()->scale.x;
            getTransform()->position.y = tileTransform->position.y;
        }

        tileSprite->setColor(glm::vec4(1.0f,0.5f,0.0f,1.0f));
        tiles[i] = tile;
    }
}

void J::resolveRotations()
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
    }
}