#include "Sandbox.hpp"
#include "Grid.hpp"
#include "CameraController.hpp"

void Sandbox::start()
{
    setWidth(1000);
    setHeight(800);
    setTitle("Life");

    Scene scene;
    setActiveScene(scene);

    auto grid = activeScene->createEntity();
    std::shared_ptr<Grid> gridPtr = std::make_shared<Grid>(grid, activeScene);
    activeScene->addComponent<Script>(grid, gridPtr);

    auto camera = activeScene->createEntity();
    std::shared_ptr<CameraController> cameraPtr = std::make_shared<CameraController>(camera, activeScene);
    activeScene->addComponent<Script>(camera, cameraPtr);

    activeScene->addComponent<Transform>(camera);
    activeScene->addComponent<Camera>(camera, true);
}

int main() 
{
    Sandbox sandbox;
    Application engine(sandbox);
    engine.start();
    return 0;
}