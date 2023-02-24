#include "Sandbox.hpp"

void Sandbox::start()
{
    setWidth(800);
    setHeight(600);
    setTitle("Sandbox");

    Scene scene;
    setActiveScene(scene);

    auto obj = std::make_shared<GameObject>();
    auto transform = obj->addTransform();
    auto sprite = obj->addSprite();

    activeScene->objects.push_back(obj);
    player = obj;
}

void Sandbox::update(float deltaTime)
{
    std::shared_ptr<Scene> scene = getActiveScene();
    std::shared_ptr<Transform> transform = player->getTransform();

    if (Input::isKeyPressed("W"))
    {
        transform->position.y -= 100 * deltaTime;
    }

    if (Input::isKeyPressed("A"))
    {
        transform->position.x -= 100 * deltaTime;
    }

    if (Input::isKeyPressed("S"))
    {
        transform->position.y += 100 * deltaTime;
    }

    if (Input::isKeyPressed("D"))
    {
        transform->position.x += 100 * deltaTime;
    }

    if (Input::isKeyDown("X"))
    {
        player->removeSprite();
    }
}

void Sandbox::stop()
{
    printf("Stopping Sandbox...\n");
}


// int main() 
// {
//     Sandbox game;
//     Application engine(game);
//     engine.start();
//     return 0;
// }