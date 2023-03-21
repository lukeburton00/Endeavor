#pragma once
#include "entt/entt.hpp"

class ScriptSystem
{
public:
    void start(std::shared_ptr<entt::registry> &registry);
    void update(std::shared_ptr<entt::registry> &registry, float &deltaTime);
};