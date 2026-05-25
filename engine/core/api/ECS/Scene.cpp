#include "Scene.hpp"
#include "Entity.hpp"
#include "DefaultComponents/transform.hpp"
#include "DefaultComponents/tag.hpp"

namespace s2f
{
	EntityId Scene::sEntityCounter{ 0 };
	EntityId Scene::sSystemCounter{ 0 };

	Entity Scene::newEntity()
	{
		Entity entity = mEntities.emplace_back(this, sEntityCounter++);
		EntityId id = entity.id();
		mRegistry.add(id, Tag{ std::string("Entity ") + std::to_string(id) });
		mRegistry.add(id, Transform{});
		return entity;
	}

	Entity Scene::newEntity(const std::string& name)
	{
		Entity entity = mEntities.emplace_back(this, sEntityCounter++);
		EntityId id = entity.id();
		mRegistry.add(id, Tag{ name });
		mRegistry.add(id, Transform{});
		return entity;
	}

	void Scene::removeEntity(Entity entity)
	{
		mEntityRemoveQueue.push_back(entity);
	}

	void Scene::update(f32 deltaTime)
	{
		for (auto& [_, system] : mSystems)
		{
			system(mEntities, deltaTime);
		}
	}

	void Scene::onFrameEnd()
	{
		if (!mEntityRemoveQueue.empty())
		{
			for (const auto& entity : mEntityRemoveQueue)
			{
				mEntities.erase(std::remove(mEntities.begin(), mEntities.end(), entity), mEntities.end());
				mRegistry.eraseAll(entity.id());
			}
			mEntityRemoveQueue.clear();
		}

		if (!mSystemRemoveQueue.empty())
		{
			for (const auto& systemID : mSystemRemoveQueue)
			{
				mSystems.erase(systemID);
			}
			mSystemRemoveQueue.clear();
		}
	}

	SystemId Scene::addSystem(const System& system)
	{
		SystemId currentID = sSystemCounter++;
		mSystems.emplace(currentID, system);
		return currentID;
	}

	void Scene::removeSystem(const SystemId& systemID)
	{
		mSystemRemoveQueue.push_back(systemID);
	}
}
