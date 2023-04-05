#pragma once

#include "Scripting/Behavior.hpp"

namespace Endeavor
{
    struct Script
    {
        std::shared_ptr<Behavior> script;

        Script(std::shared_ptr<Behavior> behavior) : script(behavior){}
    };
} // namespace Endeavor