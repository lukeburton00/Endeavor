#pragma once

#include "game.hpp"
#include <iostream>

extern Endeavor::Game* Endeavor::CreateGame();

int main(int argc, char** argv)
{
    std::cout << "Testing" << std::endl;
    Endeavor::Game* game = Endeavor::CreateGame();
    game->Run();
    delete game;
}