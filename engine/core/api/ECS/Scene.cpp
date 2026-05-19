#include "Scene.hpp"
#include "Entity.hpp"

namespace s2f
{
	EntityId Scene::sEntityCounter{ 0 };
	EntityId Scene::sSystemCounter{ 0 };

	Entity Scene::newEntity()
	{
		return mEntities.emplace_back(this, sEntityCounter++);
	}

	void Scene::removeEntity(Entity entity)
	{
		mEntitiesToRemove.push_back(entity);
	}

	void Scene::update()
	{
		for (auto& [_, system] : mSystems)
		{
			system(mEntities);
		}
	}

	void Scene::onFrameEnd()
	{
		for (const auto& entity : mEntitiesToRemove) 
		{
			mEntities.erase(std::remove(mEntities.begin(), mEntities.end(), entity), mEntities.end());
			mRegistry.eraseAll(entity.id());
		}
		mEntitiesToRemove.clear();
	}

	SystemId Scene::addSystem(const System& system)
	{
		SystemId currentID = sSystemCounter++;
		mSystems.emplace(currentID, system);
		return currentID;
	}

	void Scene::removeSystem(const SystemId& systemID)
	{
		mSystems.erase(systemID);
	}
}
