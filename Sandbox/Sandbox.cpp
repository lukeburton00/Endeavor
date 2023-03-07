#include "Sandbox.hpp"
#include "Grid.hpp"

void Sandbox::start()
{
    setWidth(1000);
    setHeight(1000);
    setTitle("Life");

    Scene scene;
    setActiveScene(scene);

    auto grid = activeScene->createEntity();
    std::shared_ptr<Grid> gridPtr = std::make_shared<Grid>(grid, activeScene);
    activeScene->addComponent<Script>(grid, gridPtr);
}

int main() 
{
    Sandbox sandbox;
    Application engine(sandbox);
    engine.start();
    return 0;
}