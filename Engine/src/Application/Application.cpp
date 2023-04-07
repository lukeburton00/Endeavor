#include "Application/Application.hpp"

#include "entt/entt.hpp"

Endeavor::Application::Application(Game& game) : mActiveGame(game) {};

void Endeavor::Application::start()
{
    #ifdef DEBUG
    printf("Initializing...\n");
    #endif

    mActiveGame.start();
    float width = mActiveGame.getWidth();
    float height = mActiveGame.getHeight();
    const char * title = mActiveGame.getTitle();

    mWindow.create(
        width, 
        height, 
        title, 
        (SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)
    );

    mPhysicsSystem = std::make_shared<PhysicsSystem>();
    mScriptSystem = std::make_shared<ScriptSystem>();
    mRenderSystem = std::make_shared<RenderSystem>();

    mRenderSystem->setOrthographicProjectionMatrix(width, height);

    loadAssets();
    loop();
}

void Endeavor::Application::loadAssets()
{
    std::string assetName = "DefaultShader";
    AssetManager::loadShader(assetName, "../../engine/assets/shaders/default.vert", "../../engine/assets/shaders/default.frag");

    assetName = "BatchShader";
    AssetManager::loadShader(assetName, "../../engine/assets/shaders/sprite_batch.vert", "../../engine/assets/shaders/sprite_batch.frag");

    assetName = "DefaultTexture";
    AssetManager::loadTexture2D(assetName, "../../engine/assets/2DTextures/default.jpg");

    mActiveGame.loadAssets();
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