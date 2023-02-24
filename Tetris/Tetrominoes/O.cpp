#include "O.hpp"

void O::buildTiles()
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
            tileTransform->position.x += tileTransform->scale.x;
            tileTransform->position.y += tileTransform->scale.y;
        }

        if (i == 3)
        {
            tileTransform->position.x -= tileTransform->scale.x;
            tileTransform->position.y += tileTransform->scale.y;
        }

        tileSprite->setColor(glm::vec4(1.0f,1.0f,0.0f,1.0f));
        tileTransform->position.y -= tileTransform->scale.y;
        if (i == 3)
        {
            getTransform()->position.y = tileTransform->position.y;
        }
        tiles[i] = tile;
    }
}

void O::resolveRotations()
{
    printf("O does not rotate.\n");
}