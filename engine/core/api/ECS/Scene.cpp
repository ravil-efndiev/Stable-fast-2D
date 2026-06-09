#include "Scene.hpp"
#include "Entity.hpp"
#include "DefaultComponents/transform.hpp"
#include "DefaultComponents/tag.hpp"
#include "DefaultSystems/defaultSystems.hpp"

namespace s2f
{
	EntityId Scene::sEntityCounter{ 0 };
	SystemId Scene::sSystemCounter{ 0 };
	
	Scene::Scene()
	{
		addSystem(spriteAnimationSystem);
	}
	
	Entity Scene::newEntity()
	{
		Entity entity = mEntities.emplace_back(this, sEntityCounter++);
		EntityId id = entity.id();
		mRegistry.add(id, Tag{ std::string("Entity ") + std::to_string(id) });
		mRegistry.add(id, Transform{});
		return entity;
	}

	Entity Scene::newEntity(std::string_view name)
	{
		Entity entity = mEntities.emplace_back(this, sEntityCounter++);
		EntityId id = entity.id();
		mRegistry.add(id, Tag{ std::string(name) });
		mRegistry.add(id, Transform{});
		return entity;
	}

	void Scene::removeEntity(Entity entity)
	{
		mEntityRemoveQueue.push_back(entity);
	}

	void Scene::update(f32 deltaTime)
	{
		for (auto& system : mSystems)
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
				mSystems.erase(std::remove_if(mSystems.begin(), mSystems.end(), 
					[systemID](const auto& system)
					{
						return systemID == system.id;
					}
				), mSystems.end());
			}
			mSystemRemoveQueue.clear();
		}
	}

	SystemId Scene::addSystem(const SystemFunc& systemFunc)
	{
		SystemId currentID = sSystemCounter++;
		mSystems.emplace_back(systemFunc, currentID);
		return currentID;
	}

	void Scene::removeSystem(SystemId systemID)
	{
		mSystemRemoveQueue.push_back(systemID);
	}
}
