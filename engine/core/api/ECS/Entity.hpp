#pragma once
#include "Scene.hpp"

namespace s2f
{
    /*
    * @brief Class that holds id of an entity added to an ECS context and provides simpler API for managing components
    */
	class Entity
	{
	public:
        // Default constructor, creates a dummy entity intance that must be initialized later
        Entity() = default;

        // Creates entity from its ID and a scene pointer, entities can only be created from API provided by Scene
		explicit Entity(Scene* scene, EntityId id) : mScene(scene), mID(id) {}

		EntityId id() const { return mID; }

        /*
        * @brief Adds a component to a registry and binds it to ID of the entity
        * @tparam ComponentT type of a component being added
        * @param args arguments for a constructor of ComponentT
        * @return pointer to a component created inside registry
        */
        template <class ComponentT, class ...Args>
        ComponentT* add(Args&&... args) const 
        {
            S2F_ASSERT(*this, sErrorStr);
            return mScene->mRegistry.add<ComponentT>(mID, ComponentT{ std::forward<Args>(args)... });
        }

        /*
        * @brief Fetches a component that should belong to the entity
        * 
        * If entity doesn't own a searched component, returns nullptr
        * @tparam ComponentT type of a searched component
        * @return pointer to a found component or nullptr
        */
        template <class ComponentT>
        ComponentT* get() const
        {
            S2F_ASSERT(*this, sErrorStr);
            return mScene->mRegistry.get<ComponentT>(mID);
        }

        /*
        * @brief Checks if component with a searched type belongs to the entity
        * @tparam ComponentT type of a searched component
        * @return boolean value that means wether entity has searched component or no
        */
        template <class ComponentT>
        bool has() const
        {
            S2F_ASSERT(*this, sErrorStr);
            return mScene->mRegistry.has<ComponentT>(mID);
        }

        /*
        * @brief Removes component belonging to the entity from component registry
        * 
        * Does nothing if component doesn't belong to the entity
        * @tparam ComponentT type of a component to remove
        */
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

#include "Scene.inl"
