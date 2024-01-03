#pragma once

#include "game.hpp"

#include <iostream>

extern Endeavor::Game* Endeavor::CreateGame();

int main(int argc, char** argv)
{
    Endeavor::Game* game = Endeavor::CreateGame();
    game->Run();
    delete game;

    return 0;
}