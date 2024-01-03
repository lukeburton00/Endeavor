#include "endeavor.hpp"

#include <iostream>

struct Player
{
    Endeavor::Sprite sprite;
    glm::vec2 position;

    Player()
    {
        sprite.scale = glm::vec2(25.f, 25.f);
        position = glm::vec2(0.f, 0.f);
    }
};

class TestGame : public Endeavor::Game
{
private:
    Endeavor::Camera m_Camera;
    Player m_Player;

public:
    virtual void Update() override
    {
        m_Camera.Update();

        if (Endeavor::Input::IsKeyPressed(Endeavor::KeyCode::W))
        {
            m_Player.position.y -= 1;
        }        
        
        if (Endeavor::Input::IsKeyPressed(Endeavor::KeyCode::A))
        {
            m_Player.position.x -= 1;
        }        
        
        if (Endeavor::Input::IsKeyPressed(Endeavor::KeyCode::S))
        {
            m_Player.position.y += 1;
        }        
        
        if (Endeavor::Input::IsKeyPressed(Endeavor::KeyCode::D))
        {
            m_Player.position.x += 1;
        }
    }

    virtual void Render() override
    {
        auto renderer = Endeavor::Renderer::GetInstance();
        renderer->Begin(m_Camera);
        renderer->RenderSprite(m_Player.position, m_Player.sprite);
        renderer->Draw();
    }

};

Endeavor::Game* Endeavor::CreateGame()
{
    return new TestGame();
}