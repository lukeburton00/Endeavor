#pragma once
#include <string>
#include <vector>
#include "Graphics/Window.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include "ResourceManager.hpp"
#include "Game.hpp"
#include "Renderer.hpp"

class Application
{
public:
    Application(Game& game);
    void start();
    
private:
    Game& mActiveGame;

    Window mWindow;
    bool mGameIsRunning;

    std::shared_ptr<Renderer> mRenderer;

    void loop();

    void processInput();
    void update(float deltaTime);
    void render();

    void quit();
};