#include "ECS/System/ScriptSystem.hpp"
#include "ECS/Component/Script.hpp"

void Endeavor::ScriptSystem::start(std::shared_ptr<entt::registry> &registry)
{
    auto view = registry->view<Script>();

    for (auto entity : view)
    {
        auto &script = view.get<Script>(entity);
        script.script->start();
    }
}

void Endeavor::ScriptSystem::update(std::shared_ptr<entt::registry> &registry, float &deltaTime)
{
    auto view = registry->view<Script>();

    for (auto entity : view)
    {
        auto &script = view.get<Script>(entity);

        script.script->update(deltaTime);
    }
}