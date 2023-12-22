#include "endeavor.hpp"

#include <iostream>

class TestGame : public Endeavor::Game
{
public:
    virtual void Update() override
    {
        std::cout << "Update" << std::endl;
    }

    virtual void Render() override
    {
        std::cout << "Render" << std::endl;
    }
};

Endeavor::Game* Endeavor::CreateGame()
{
    return new TestGame();
}