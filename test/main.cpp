#include "endeavor.hpp"

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

    while (true)
    {
        Endeavor::Input::processInput();

        if (Endeavor::Input::isKeyDown("Q") || Endeavor::Input::quit)
        {
            break;
        }

        window.clear();

        batch.draw( glm::vec2(0, 0), glm::vec2(100, 100), glm::vec4 (1, 1, 1, 1), "default_tex", "default_shader");

        batch.flush();
        // draw here

        window.swapBuffers();
    }

    window.destroy();

    return 0;
}