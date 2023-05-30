#include "endeavor.hpp"
#include "player.hpp"

#include <iostream>

#ifdef _WIN32
#include <SDL.h>
#undef main
#endif

int main (int argc, char **argv)
{
    Endeavor::Window window;
    window.create(800, 600, "Test");

    Endeavor::SpriteBatch batch;

    Endeavor::AssetManager::loadTexture2D("default_tex", "../assets/2DTextures/default.jpg");
    Endeavor::AssetManager::loadTexture2D("dungeon_sheet", "../assets/2DTextures/tiny_dungeon/Tilemap/tilemap_packed.png");
    Endeavor::AssetManager::loadShader("default_shader", "../assets/shaders/sprite_batch.vert", "../assets/shaders/sprite_batch.frag");

    glm::mat4 projectionMatrix = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -0.1f, 0.1f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);

    batch.setProjectionMatrix( projectionMatrix );
    batch.setViewMatrix( viewMatrix );

    Player player;
    player.moveSpeed = 100.0f;

    int frames = 0;
    float elapsed_time = 0;

    Endeavor::Time time;
    float deltaTime = 0;

    while (true)
    {
        time.start();

        Endeavor::Input::processInput();

        if (Endeavor::Input::isKeyDown("Q") || Endeavor::Input::quit)
        {
            break;
        }

        player.update(deltaTime);

        window.clear();

        batch.drawSubTexture(glm::vec2(100,100),glm::vec2(50,50), glm::vec4(1,1,1,1), "dungeon_sheet", glm::vec2(0,6), glm::vec2(16,16), "default_shader"); 
        player.draw(batch);
        batch.flush();

        window.swapBuffers();

        time.stop();
        deltaTime = time.getElapsedTime();

        elapsed_time += deltaTime;
        frames++;

        if (elapsed_time > 1)
        {
            std::cout << frames / elapsed_time << " FPS, Draw Calls: " << Endeavor::SpriteBatch::numDrawCalls << std::endl;
            elapsed_time = 0;
            frames = 0;
        }

        Endeavor::SpriteBatch::numDrawCalls = 0;

    }
    window.destroy();

    return 0;
}