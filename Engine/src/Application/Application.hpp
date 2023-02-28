#pragma once
#include <string>
#include <vector>
#include "Graphics/Window.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "PhysicsSystem.hpp"
#include "RenderSystem.hpp"

class Application
{
public:
    Application(Game& game);
    void start();
    
private:
    Game& mActiveGame;

    Window mWindow;
    bool mGameIsRunning;

    std::shared_ptr<PhysicsSystem> mPhysicsSystem;
    std::shared_ptr<RenderSystem> mRenderSystem;

    void loop();

    void processInput();
    void update(float deltaTime);
    void render();

    void quit();
};