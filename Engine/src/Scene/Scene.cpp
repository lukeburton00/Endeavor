#include "Scene.hpp"
#include "Entity.hpp"

Entity Scene::createEntity()
{
    Entity entity(mRegistry->create(), this);
    return entity;
}

void Scene::destroyEntity(entt::entity entity)
{
    mRegistry->destroy(entity);
}