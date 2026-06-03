#pragma once
#include "Entity.hpp"

namespace s2f
{
    template <class ComponentT, class ...Args>
    ComponentT* Scene::addComponent(Entity entity, Args&&... args) 
    {
        return mRegistry.add<ComponentT>(entity.id(), ComponentT{ std::forward<Args>(args)... });
    }

    template <class ComponentT>
    ComponentT* Scene::getComponent(Entity entity)
    {
        return mRegistry.get<ComponentT>(entity.id());
    }

    template <class ComponentT>
    bool Scene::hasComponent(Entity entity)
    {
        return mRegistry.has<ComponentT>(entity.id());
    }

    template <class ComponentT>
    void Scene::removeComponent(Entity entity)
    {
        mRegistry.remove<ComponentT>(entity.id());
    }
}
