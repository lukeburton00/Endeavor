#include "Scene.hpp"

entt::entity Scene::createEntity()
{
    return mRegistry->create();
}

void Scene::destroyEntity(entt::entity entity)
{
    mRegistry->destroy(entity);
}

std::shared_ptr<entt::registry> Scene::getRegistry()
{
    return mRegistry;
}