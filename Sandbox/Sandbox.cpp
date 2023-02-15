#include "Sandbox.hpp"

void Sandbox::start()
{
    setWidth(800);
    setHeight(600);
    setTitle("Sandbox");

    Scene scene;

    GameObject obj;
    obj.id = 1;
    obj.addTransform();

    scene.objects.push_back(obj);
    setActiveScene(scene);
}

void Sandbox::update(float deltaTime)
{
    std::shared_ptr<Scene> scene = getActiveScene();
    std::shared_ptr<Transform> transform = scene->objects[0].getTransform();

    if (Input::isKeyPressed("W"))
    {
        transform->position.y += 100 * deltaTime;
    }

    if (Input::isKeyPressed("A"))
    {
        transform->position.x -= 100 * deltaTime;
    }

    if (Input::isKeyPressed("S"))
    {
        transform->position.y -= 100 * deltaTime;
    }

    if (Input::isKeyPressed("D"))
    {
        transform->position.x += 100 * deltaTime;
    }
}

void Sandbox::stop()
{
    printf("Stopping Sandbox...\n");
}

int main() 
{
    Sandbox game;
    Application engine(game);
    engine.start();
    return 0;
}