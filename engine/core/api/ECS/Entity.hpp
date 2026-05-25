#pragma once
#include "Scene.hpp"

namespace s2f
{
	class Entity
	{
	public:
        Entity() = default;
		explicit Entity(Scene* scene, EntityId id) : mScene(scene), mID(id) {}

		EntityId id() const { return mID; }

        template <class ComponentT, class ...Args>
        ComponentT* add(Args&&... args) const 
        {
            S2F_ASSERT(*this, sErrorStr);
            return mScene->mRegistry.add<ComponentT>(mID, ComponentT{ std::forward<Args>(args)... });
        }

        template <class ComponentT>
        ComponentT* get() const
        {
            S2F_ASSERT(*this, sErrorStr);
            return mScene->mRegistry.get<ComponentT>(mID);
        }

        template <class ComponentT>
        bool has() const
        {
            S2F_ASSERT(*this, sErrorStr);
            return mScene->mRegistry.has<ComponentT>(mID);
        }

        template <class ComponentT>
        void remove() const
        {
            S2F_ASSERT(*this, sErrorStr);
            mScene->mRegistry.remove<ComponentT>(mID);
        }

        operator bool() const
        {
            return mScene != nullptr;
        }

	private:
		Scene* mScene;
		EntityId mID;
        static constexpr char sErrorStr[] { "Entity wasn't initialized or doesnt belong to the scene" };
	};
}
