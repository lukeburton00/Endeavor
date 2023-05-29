#include "endeavor.hpp"
#include "player.hpp"

#include <iostream>

int main (int argc, char **argv)
{
    Endeavor::Window window;
    window.create(800, 600, "Test");

    Endeavor::SpriteBatch batch;

    Endeavor::AssetManager::loadTexture2D("default_tex", "../assets/2DTextures/default.jpg");
    Endeavor::AssetManager::loadShader("default_shader", "../assets/shaders/sprite_batch.vert", "../assets/shaders/sprite_batch.frag");

    glm::mat4 projectionMatrix = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -0.1f, 0.1f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);

    batch.setProjectionMatrix( projectionMatrix );
    batch.setViewMatrix( viewMatrix );

    Player player;
    player.scale = glm::vec2(50,50);
    player.moveSpeed = 100.0f;

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

        batch.draw( player.position, player.scale, glm::vec4 (1, 1, 1, 1), "default_tex", "default_shader");

        batch.flush();

        window.swapBuffers();

        time.stop();
        deltaTime = time.getElapsedTime();
    }

    window.destroy();

    return 0;
}