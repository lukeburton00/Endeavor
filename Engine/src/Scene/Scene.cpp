#include "Scene.hpp"

Entity Scene::createEntity()
{
    return mRegistry->create();
}

void Scene::destroyEntity(Entity entity)
{
    mRegistry->destroy(entity);
}

std::shared_ptr<Registry> Scene::getRegistry()
{
    return mRegistry;
}