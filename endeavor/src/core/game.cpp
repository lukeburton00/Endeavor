#include "game.hpp"

#include <thread>
#include <chrono>
#include <iostream>

namespace Endeavor
{
    Game::Game()
    : m_Window(WindowProperties("Endeavor", 800, 600))
    {

    }

    Game::~Game()
    {

    }

    void Game::Run()
    {
        m_Window.Init();

        while (!m_Window.quit)
        {
            m_Window.Update();
            Update();

            m_Window.Clear(1,1,1);
            Render();
            m_Window.SwapBuffers();
        }
    }
}// namespace Endeavor