#include "ScriptSystem.hpp"
#include "Script.hpp"

void ScriptSystem::start(std::shared_ptr<entt::registry> &registry)
{
    auto view = registry->view<Script>();

    for (auto entity : view)
    {
        auto &script = view.get<Script>(entity);
        script.script->start();
    }
}

void ScriptSystem::update(std::shared_ptr<entt::registry> &registry, float &deltaTime)
{
    auto view = registry->view<Script>();

    for (auto entity : view)
    {
        auto &script = view.get<Script>(entity);

        script.script->update(deltaTime);
    }
}