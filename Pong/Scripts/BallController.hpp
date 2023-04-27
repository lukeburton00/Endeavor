#pragma once

#include "Engine.hpp"
using namespace Endeavor;

class BallController : public Behavior
{
public:

    using Behavior::Behavior;

    float movementSpeedX;
    float movementSpeedY;

    std::shared_ptr<Entity> paddleOne;
    std::shared_ptr<Entity> paddleTwo;

    void start() override
    {
        movementSpeedX = 200.0f;
        movementSpeedY = 0.0f;
    }

    void update(const float& deltaTime) override
    {
        auto &transform = self.getComponent<Transform>();

        transform.position.x += movementSpeedX * deltaTime;
        transform.position.y += movementSpeedY * deltaTime;
        checkYBounds();

        if (transform.position.x < 100)
        {
            checkCollisionWithPlayerOne();
        }

        if (transform.position.x > 700)
        {
            checkCollisionWithPlayerTwo();
        }
    }

private:

    void checkCollisionWithPlayerOne()
    {
        auto transform = self.getComponent<Transform>();
        auto playerOneTransform = paddleOne->getComponent<Transform>();

        if (transform.position.x < playerOneTransform.position.x + playerOneTransform.scale.x
        && transform.position.x > playerOneTransform.position.x)
        {
            if (transform.position.y > playerOneTransform.position.y 
            && transform.position.y < playerOneTransform.position.y + playerOneTransform.scale.y)
            {
                movementSpeedX -= 30.0f;
                movementSpeedX *= -1.0f;

                float playerOneYCenter = playerOneTransform.position.y + (playerOneTransform.scale.y / 2);
                float ballYCenter = transform.position.y + (transform.scale.y / 2);

                movementSpeedY = ballYCenter - playerOneYCenter;
            }
        }
    }

    void checkCollisionWithPlayerTwo()
    {
        auto transform = self.getComponent<Transform>();
        auto playerTwoTransform = paddleTwo->getComponent<Transform>();

        if (((transform.position.x + transform.scale.x) > playerTwoTransform.position.x)
            && (transform.position.x < (playerTwoTransform.position.x + playerTwoTransform.scale.x)))
        {
            if (transform.position.y > playerTwoTransform.position.y 
            && transform.position.y < playerTwoTransform.position.y + playerTwoTransform.scale.y)
            {
                movementSpeedX += 30.0f;
                movementSpeedX *= -1.0f;

                float playerTwoYCenter = playerTwoTransform.position.y + (playerTwoTransform.scale.y / 2);
                float ballYCenter = transform.position.y + (transform.scale.y / 2);

                movementSpeedY = ballYCenter - playerTwoYCenter;
            }
        }
    }

    void checkYBounds()
    {
        auto transform = self.getComponent<Transform>();

        if (transform.position.y < 0.0f || transform.position.y + transform.scale.y > 800.0f)
        {
            movementSpeedY *= -1.0f;
        }
    }
};