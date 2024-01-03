#include "game.hpp"

#include "renderer/renderer.hpp"

#include <thread>
#include <chrono>
#include <iostream>

namespace Endeavor
{
    Game* Game::s_Instance = nullptr;

    Game::Game()
    : m_Window(WindowProperties("Endeavor", 800, 600))
    {
        s_Instance = this;
    }

    void Game::Run()
    {
        m_Window.Init();
        Renderer::GetInstance()->Init();

        while (!m_Window.quit)
        {
            m_Window.Update();
            Update();

            m_Window.Clear(0.f, 0.f, 0.f);
            Render();
            m_Window.SwapBuffers();
        }
    }
}// namespace Endeavor