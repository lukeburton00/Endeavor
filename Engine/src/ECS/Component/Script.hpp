#pragma once
#include "Behavior.hpp"

struct Script
{
    std::shared_ptr<Behavior> script;

    Script(std::shared_ptr<Behavior> behavior) : script(behavior){}
};