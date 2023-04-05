#include "Scene/Scene.hpp"

#include "ECS/Entity/Entity.hpp"

Endeavor::Entity Endeavor::Scene::createEntity()
{
    Entity entity(mRegistry->create(), this);
    return entity;
}

void Endeavor::Scene::destroyEntity(entt::entity entityHandle)
{
    mRegistry->destroy(entityHandle);
}