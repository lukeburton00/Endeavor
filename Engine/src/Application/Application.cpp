#include "Application.hpp"
#include "entt/entt.hpp"

Application::Application(Game& game) : mActiveGame(game) {};

void Application::start()
{
    entt::registry registry;
    auto entity = registry.create();
    #ifdef DEBUG
    printf("Initializing...\n");
    #endif

    mActiveGame.start();
    mWindow.create(
        mActiveGame.getWidth(), 
        mActiveGame.getHeight(), 
        mActiveGame.getTitle(), 
        (SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)
    );

    std::string title = "DefaultShader";
    ResourceManager::loadShader(title, "../engine/assets/shaders/default.vert", "../engine/assets/shaders/default.frag");

    title = "DefaultTexture";
    ResourceManager::loadTexture2D(title, "../engine/assets/2DTextures/default.jpg");

    title = "GridTexture";
    ResourceManager::loadTexture2D(title, "../engine/assets/2DTextures/grid.png");

    title = "TileTexture";
    ResourceManager::loadTexture2D(title, "../engine/assets/2DTextures/tile.png");

    mRenderer = std::make_shared<Renderer>(glm::vec2(mActiveGame.getWidth(), mActiveGame.getHeight()));

    loop();
}

void Application::loop()
{
    #ifdef DEBUG
    printf("Running...\n\n");
    int frames = 0;
    int framesPerSecond = 0;
    float elapsedTime = 0.0f;
    #endif

    Time timer;
    float deltaTime = 0;

    mGameIsRunning = true;
    while (mGameIsRunning)
    {
        timer.start();
        processInput();
        update(deltaTime);
        render();
        timer.stop();
        deltaTime = timer.getElapsedTime();

        #ifdef DEBUG
        frames++;
        elapsedTime += deltaTime;
        if (elapsedTime >= 1)
        {
            framesPerSecond = frames/elapsedTime;
            printf("FPS: %d\n", framesPerSecond);
            elapsedTime = 0;
            frames = 0;
        }
        #endif
    }

    #ifdef DEBUG
    printf("Game stopped.\n");
    #endif
}

void Application::processInput()
{
    Input::processInput();
    if(Input::quit){ quit(); return; }

    if (Input::isKeyPressed("Escape"))
    {
        quit();
    }
} 

void Application::update(float deltaTime)
{
    std::shared_ptr<Scene> scene = mActiveGame.getActiveScene();

    for (auto& obj : scene->objects)
    {
        obj->update(deltaTime);
    }

    mActiveGame.update(deltaTime);
}

void Application::render()
{
    mWindow.clear();
    std::shared_ptr<Scene> scene = mActiveGame.getActiveScene();

    for (auto const& obj : scene->objects)
    {
        auto transform = obj->getTransform();
        auto sprite = obj->getSprite();
        if (transform != nullptr && sprite != nullptr)
        {
            mRenderer->drawQuad(transform->position, transform->scale, sprite->color, sprite->textureName);
        }
    }

    mWindow.swapBuffers();
}

void Application::quit()
{
    mActiveGame.stop();
    mGameIsRunning = false;
    mWindow.destroy();
    SDL_Quit();
}