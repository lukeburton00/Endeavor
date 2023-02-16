#pragma once
#include "Engine.hpp"

class Tetris : public Game
{
public:
    void start() override;
    void update(float deltaTime) override;
    void stop() override;

private:
    Time timer;
    float elapsedTime;
};