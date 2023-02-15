#pragma once
#include "Engine.hpp"

class Sandbox : public Game
{
public:
    void start() override;
    void update(float deltaTime) override;
    void stop() override;

private:
    Time timer;
};