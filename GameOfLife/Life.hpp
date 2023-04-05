#pragma once
#include "Engine.hpp"

using namespace Endeavor;

class Life : public Game
{
public:
    void start() override;

private:
    Time timer;
};