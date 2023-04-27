#pragma once

#include "Engine.hpp"

using namespace Endeavor;

class Pong : public Game
{
    void start() override;
    void update(float dt) override;
    void createPlayers();
};