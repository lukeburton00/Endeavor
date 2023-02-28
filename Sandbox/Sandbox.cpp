#include "Sandbox.hpp"

void Sandbox::start()
{
    setWidth(800);
    setHeight(600);
    setTitle("Sandbox");

    Scene scene;
    setActiveScene(scene);

    auto entity = activeScene->createEntity();
    activeScene->addComponent<Transform>(entity);
    activeScene->addComponent<Sprite>(entity);
}

void Sandbox::update(float deltaTime)
{

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