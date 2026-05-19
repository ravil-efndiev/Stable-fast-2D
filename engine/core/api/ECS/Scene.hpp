#pragma once
#include "system.hpp"
#include "ComponentRegistry.hpp"

namespace s2f
{
	class Scene
	{
	public:
		friend class Entity;

	public:
		Scene() = default;
		~Scene() = default;

		Entity newEntity();
		void removeEntity(Entity entity);

		void update();
		void onFrameEnd();
	
		SystemId addSystem(const System& system);
		void removeSystem(const SystemId& systemID);

		std::vector<Entity> entities() const { return mEntities; }

	private:
		std::unordered_map<SystemId, System> mSystems;
		ComponentRegistry mRegistry;
		std::vector<Entity> mEntities;

		std::vector<Entity> mEntitiesToRemove;

		static EntityId sEntityCounter;
		static EntityId sSystemCounter;
	};
}
