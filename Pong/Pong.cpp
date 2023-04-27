#include "Pong.hpp"

#include "PlayerOneController.hpp"
#include "PlayerTwoController.hpp"
#include "BallController.hpp"

void Pong::start()
{
    setWidth(800);
    setHeight(600);
    setTitle("Pong");

    Scene scene;
    setActiveScene(scene);

    createPlayers();
}

void Pong::update(float dt)
{
    if (Input::isKeyPressed("Escape"))
    {
        Input::stop();
    }
}

void Pong::createPlayers()
{
    Entity paddle = activeScene->createEntity("PlayerOne");

    auto &transform = paddle.addComponent<Transform>();
    auto &sprite = paddle.addComponent<Sprite>();

    transform.scale = glm::vec3(25.0f, 100.0f, 1.0f);
    transform.position = glm::vec3(50.0f, 400.0f, 0.0f);

    auto playerOneController = std::make_shared<PlayerOneController>(paddle, activeScene);
    paddle.addComponent<Script>(playerOneController);

    Entity paddle2 = activeScene->createEntity("PlayerTwo");

    auto &transform2 = paddle2.addComponent<Transform>();
    auto &sprite2 = paddle2.addComponent<Sprite>();

    transform2.scale = glm::vec3(25.0f, 100.0f, 1.0f);
    transform2.position = glm::vec3(750.0f, 400.0f, 0.0f);

    auto playerTwoController = std::make_shared<PlayerTwoController>(paddle2, activeScene);
    paddle2.addComponent<Script>(playerTwoController);

    Entity ball = activeScene->createEntity("Ball");

    auto &transform3 = ball.addComponent<Transform>();
    auto &sprite3 = ball.addComponent<Sprite>();

    transform3.scale = glm::vec3(10.0f, 10.0f, 1.0f);
    transform3.position = glm::vec3(400.0f, 300.0f, 0.0f);

    auto ballController = std::make_shared<BallController>(ball, activeScene);
    ball.addComponent<Script>(ballController);

    ballController->paddleOne = std::make_shared<Entity>(paddle);
    ballController->paddleTwo = std::make_shared<Entity>(paddle2);
}

int main() 
{
    Pong pong;
    Application engine(pong);
    engine.start();
    return 0;
}