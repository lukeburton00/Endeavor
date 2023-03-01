#pragma once
#include "entt/entt.hpp"

class ScriptSystem
{
public:
    void update(std::shared_ptr<entt::registry> registry, float deltaTime);
};