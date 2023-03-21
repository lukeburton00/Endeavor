#include "Sandbox.hpp"
#include "Grid.hpp"
#include "CameraController.hpp"

void Sandbox::start()
{
    setWidth(1000);
    setHeight(1000);
    setTitle("Life");

    Scene scene;
    setActiveScene(scene);

    auto grid = activeScene->createEntity();
    std::shared_ptr<Grid> gridPtr = std::make_shared<Grid>(grid, activeScene);
    grid.addComponent<Script>(gridPtr);

    auto camera = activeScene->createEntity();
    std::shared_ptr<CameraController> cameraPtr = std::make_shared<CameraController>(camera, activeScene);
    camera.addComponent<Script>(cameraPtr);

    camera.addComponent<Transform>();
    camera.addComponent<Camera>(true);
}

int main() 
{
    Sandbox sandbox;
    Application engine(sandbox);
    engine.start();
    return 0;
}