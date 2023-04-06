#include "Application/Application.hpp"

#include "entt/entt.hpp"

Endeavor::Application::Application(Game& game) : mActiveGame(game) {};

void Endeavor::Application::start()
{
    #ifdef DEBUG
    printf("Initializing...\n");
    #endif

    mPhysicsSystem = std::make_shared<PhysicsSystem>();
    mScriptSystem = std::make_shared<ScriptSystem>();

    mActiveGame.start();
    mWindow.create(
        mActiveGame.getWidth(), 
        mActiveGame.getHeight(), 
        mActiveGame.getTitle(), 
        (SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)
    );

    std::string title = "DefaultShader";
    AssetManager::loadShader(title, "../../engine/assets/shaders/default.vert", "../../engine/assets/shaders/default.frag");

    title = "BatchShader";
    AssetManager::loadShader(title, "../../engine/assets/shaders/sprite_batch.vert", "../../engine/assets/shaders/sprite_batch.frag");

    title = "DefaultTexture";
    AssetManager::loadTexture2D(title, "../../engine/assets/2DTextures/default.jpg");

    title = "GridTexture";
    AssetManager::loadTexture2D(title, "../../engine/assets/2DTextures/grid.png");

    title = "TileTexture";
    AssetManager::loadTexture2D(title, "../../engine/assets/2DTextures/tile.png");

    mRenderSystem = std::make_shared<RenderSystem>();
    float width = mActiveGame.getWidth();
    float height = mActiveGame.getHeight();
    mRenderSystem->setOrthographicProjectionMatrix(width, height);

    loop();
}

void Endeavor::Application::loop()
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

    auto registry = mActiveGame.getActiveScene()->getRegistry();
    mScriptSystem->start(registry);

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

void Endeavor::Application::processInput()
{
    Input::processInput();
    if(Input::quit){ quit(); return; }
} 

void Endeavor::Application::update(float deltaTime)
{
    auto registry = mActiveGame.getActiveScene()->getRegistry();

    mRenderSystem->updateProjection(registry);
    mPhysicsSystem->update(registry, deltaTime);
    mActiveGame.update(deltaTime);
    mScriptSystem->update(registry, deltaTime);
}

void Endeavor::Application::render()
{
    mWindow.clear();

    auto registry = mActiveGame.getActiveScene()->getRegistry();
    mRenderSystem->update(registry);

    mWindow.swapBuffers();
}

void Endeavor::Application::quit()
{
    mActiveGame.stop();
    mGameIsRunning = false;
    mWindow.destroy();
    SDL_Quit();
}