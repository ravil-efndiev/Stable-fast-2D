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
