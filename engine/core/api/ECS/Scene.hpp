#pragma once
#include "system.hpp"
#include "ComponentRegistry.hpp"

namespace s2f
{
	/*
	* @brief Class that represents an ECS context
	* 
	* Contains list of entities, registry of components and list of systems
	* 
	* Responsible for providing interface for ECS, managing components, updating and managing systems
	*/
	class Scene
	{
	public:
		friend class Entity;

	public:
		// Constructor is also responsible for adding all default systems from defaultSystems.hpp
		Scene();
		~Scene() = default;

		/*
		* @brief Creates a new entity object and pushed it to internal storage
		* @return Entity object (returned by value since Entity is only meant to hold an ID)
		*/
		Entity newEntity();

		/*
		* @brief Creates a new entity object and pushed it to internal storage
		* @param name name string for default-added Tag component
		* @return Entity object (returned by value since Entity is only meant to hold an ID)
		*/
		Entity newEntity(const std::string& name);

		/*
		* @brief Adds entity to a remove queue, removals are processed at the end of a frame
		* @param entity entity to remove from scene
		*/
		void removeEntity(Entity entity);

		/*
		* @brief Runs scene's systems, should be called before rendering stage
		* @param deltaTime time difference between frames, also accessible via Time::delta()
		*/
		void update(f32 deltaTime);

		/*
		* @brief Performs post-update operations, should be called after all update and render code
		* 
		* Responsible for executing entity and system removals
		*/
		void onFrameEnd();
	
		/*
		* @brief Gives each system its unique ID and adds it to a system storage
		* @return id of an added system, it can be used to call removeSystem
		*/
		SystemId addSystem(const System& system);

		/*
		* @brief Adds system to a system removal queue, removals are processed at the end of a frame
		* @param systemID id given to a system on addSystem() call
		*/
		void removeSystem(const SystemId& systemID);

		/*
        * @brief Adds a component to a registry and binds it to ID of the entity
        * @tparam ComponentT type of a component being added
        * @param args arguments for a constructor of ComponentT
		* @param entity entity to add component to
		* @return pointer to a component created inside registry
        */
        template <class ComponentT, class ...Args>
        ComponentT* addComponent(Entity entity, Args&&... args);

        /*
        * @brief Fetches a component that should belong to the entity
        * 
        * If entity doesn't own a searched component, returns nullptr
        * @tparam ComponentT type of a searched component
		* @param entity entity to get component of
        * @return pointer to a found component or nullptr
        */
        template <class ComponentT>
        ComponentT* getComponent(Entity entity);

        /*
        * @brief Checks if component with a searched type belongs to the entity
        * @tparam ComponentT type of a searched component
		* @param entity entity to check if component belongs to
        * @return boolean value that means wether entity has searched component or no
        */
        template <class ComponentT>
        bool hasComponent(Entity entity);

        /*
        * @brief Removes component belonging to the entity from component registry
        * 
        * Does nothing if component doesn't belong to the entity
        * @tparam ComponentT type of a component to remove
		* @param entity entity to remove component from
        */
        template <class ComponentT>
        void removeComponent(Entity entity);

		std::vector<Entity> entities() const { return mEntities; }

	private:
		std::unordered_map<SystemId, System> mSystems;
		ComponentRegistry mRegistry;
		std::vector<Entity> mEntities;

		std::vector<Entity> mEntityRemoveQueue;
		std::vector<SystemId> mSystemRemoveQueue;

		static EntityId sEntityCounter;
		static EntityId sSystemCounter;
	};
}
