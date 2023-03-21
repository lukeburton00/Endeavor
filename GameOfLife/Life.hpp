#pragma once
#include "Engine.hpp"

class Sandbox : public Game
{
public:
    void start() override;

private:
    Time timer;
};