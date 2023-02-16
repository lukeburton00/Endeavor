#include "Tetris.hpp"
#include "Tetromino.hpp"

void Tetris::start()
{
    setWidth(800);
    setHeight(600);
    setTitle("Tetris");


    Tetromino tetromino;
    Scene scene;
    setActiveScene(scene);

    elapsedTime = 0;
}

void Tetris::update(float deltaTime)
{
    std::shared_ptr<Scene> scene = getActiveScene();
    elapsedTime += deltaTime;
}

void Tetris::stop()
{
    printf("Stopping Sandbox...\n");
}



int main() 
{
    Tetris game;
    Application engine(game);
    engine.start();
    return 0;
}