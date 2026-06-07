#pragma once
#include "ComponentPool.hpp"
#include "component.hpp"

namespace s2f
{
    class ComponentRegistry
    {
    public:
        ComponentRegistry() = default;
        ~ComponentRegistry() = default;

        template<class ComponentT>
        ComponentT* add(EntityId entityId, const ComponentT& component)
        {
            auto* cmp = getOrCreateStorage<ComponentT>().add(entityId, component);
            if (!cmp) Logger::error("Component already exists on an entity");
            return cmp;
        }

        template<class ComponentT>
        ComponentT* get(EntityId entityId)
        {
            auto* cmp = getOrCreateStorage<ComponentT>().get(entityId);
            if (!cmp) Logger::error("Component does not exist in an entity");
            return cmp;
        }

        template<class ComponentT>
        bool has(EntityId entityId)
        {
            return getOrCreateStorage<ComponentT>().has(entityId);
        }

        template<class ComponentT>
        void remove(EntityId entityId)
        {
            getOrCreateStorage<ComponentT>().remove(entityId);
        }

        void eraseAll(EntityId entityId)
        {
            for (auto& storage : mAllStorages)
            {
                if (!storage) continue;
                storage->remove(entityId);
            }
        }

    private:
        template <class ComponentT>
        ComponentPool<ComponentT>& getOrCreateStorage()
        {
            ComponentTypeId type = getComponentType<ComponentT>();

            if (type >= mAllStorages.size())
                mAllStorages.resize((size_t)type + 1);

            if (!mAllStorages[type])
                mAllStorages[type] = std::make_unique<ComponentPool<ComponentT>>();

            return *static_cast<ComponentPool<ComponentT>*>(mAllStorages[type].get());
        }

        std::vector<std::unique_ptr<IComponentPool>> mAllStorages;
    };
}
