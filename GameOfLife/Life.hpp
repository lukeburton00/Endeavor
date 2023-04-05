#pragma once
#include "Engine.hpp"

class Life : public Game
{
public:
    void start() override;

private:
    Time timer;
};