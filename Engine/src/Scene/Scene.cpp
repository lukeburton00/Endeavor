#include "Scene/Scene.hpp"

#include "ECS/Entity/Entity.hpp"
#include "ECS/Component/Transform.hpp"
#include "ECS/Component/Tag.hpp"

Endeavor::Entity Endeavor::Scene::createEntity(const std::string& name)
{
    Entity entity(mRegistry->create(), this);
    
    addComponent<Transform>(entity.getHandle());
    addComponent<Tag>(entity.getHandle(), name);

    return entity;
}

void Endeavor::Scene::destroyEntity(Entity entity)
{
    mRegistry->destroy(entity.getHandle());
}