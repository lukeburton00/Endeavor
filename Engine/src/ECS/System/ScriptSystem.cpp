#include "ScriptSystem.hpp"
#include "Script.hpp"

void ScriptSystem::update(std::shared_ptr<entt::registry> registry, float deltaTime)
{
    auto view = registry->view<Script>();

    for (auto entity : view)
    {
        auto &script = view.get<Script>(entity);

        script.script->update(deltaTime);
    }
}