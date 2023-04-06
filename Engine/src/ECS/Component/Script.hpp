#pragma once

#include "Scripting/Behavior.hpp"

namespace Endeavor
{
    struct Script
    {
        std::shared_ptr<Behavior> behavior;

        Script(std::shared_ptr<Behavior> behaviorPtr) : behavior(behaviorPtr){}
    };
} // namespace Endeavor