#include "defaultSystems.hpp"
#include "api/ECS/entityQuery.hpp"
#include "api/Random.hpp"

namespace s2f
{
	void spriteAnimationSystem(const std::vector<Entity>& entities, f32 deltaTime)
	{
		for (auto&& [sprite, animator] : queryComponents<Sprite, SpriteAnimator>(entities))
		{
			if (animator.animations.empty()) continue;
			if (animator.currentAnimationFinished()) continue;

			RectU gridCell = animator.currentAnimation()->subtextureGridCell();
			sprite.setSubTextureFromGrid(gridCell.position, gridCell.size);
		}
	}

	void particleSystem(const std::vector<Entity>& entities, f32 deltaTime)
	{
		for (auto&& [emitter] : queryComponents<ParticleEmitter>(entities))
		{
			for (auto& particle : emitter.particles)
			{
				if (!particle.active) continue;

				if (particle.lifetimeRemaining <= 0.f)
				{
					particle.active = false;
					continue;
				}

				particle.lifetimeRemaining -= deltaTime;
				particle.position += particle.velocity * deltaTime;
				
				if (particle.rotationChange > 0.f)
					particle.rotation += 
						Random::float32Range(-1.f, 1.f) * glm::two_pi<f32>() * particle.rotationChange * deltaTime;
			}
		}
	}

    void colliderPositionSystem(const std::vector<Entity>& entities, f32 deltaTime)
    {
		for (auto&& [transform, collider] : queryComponents<Transform, Collider>(entities))
		{
			collider.bounds.position = transform.position + glm::vec3(collider.offset, 0.f);
		}

		for (auto&& [transform, colliderList] : queryComponents<Transform, ColliderList>(entities))
		{
			for (auto& coll : colliderList.colliders)
				coll.bounds.position = transform.position + glm::vec3(coll.offset, 0.f);
		}
    }

    void rigidbodySystemF(const std::vector<Entity>& entities, f32 fixedDeltaTime)
    {
		for (auto&& [transform, rigidbody] : queryComponents<Transform, Rigidbody>(entities))
		{
			glm::vec2 acceleration = rigidbody.forces * rigidbody.massInverse;
			rigidbody.velocity += acceleration * fixedDeltaTime;
			rigidbody.velocity *= glm::max(0.f, 1.f - rigidbody.linearDamping * fixedDeltaTime);
			transform.position += glm::vec3(rigidbody.velocity, 0.f) * fixedDeltaTime;
			rigidbody.forces = glm::vec2(0.f);
		}
    }

    void rigidbodyCollisionSystem(const std::vector<Entity>& entities, f32 deltaTime)
    {
		for (auto&& [colliderA, rigidbodyA] : queryComponents<Collider, Rigidbody>(entities))
		{
			if (!rigidbodyA.resolveCollisions || colliderA.isTrigger) continue;
			for (auto&& [colliderB, rigidbodyB] : queryComponents<Collider, Rigidbody>(entities))
			{
				if (!rigidbodyB.resolveCollisions || colliderB.isTrigger) continue;
				RectIntersectionInfo intInfo{};
				bool intersects = intersectionInfo(colliderA.bounds, colliderB.bounds, intInfo);

				if (!intersects) continue;
				
				f32 invMassSum = rigidbodyA.massInverse + rigidbodyB.massInverse;
				if (invMassSum == 0.0f) continue;

				f32 vn = glm::dot(rigidbodyA.velocity - rigidbodyB.velocity, intInfo.normal);
				if (vn > 0.f) continue;

				f32 e = glm::min(rigidbodyA.restitution, rigidbodyB.restitution);
				f32 j = -(1.f + e) * vn / (invMassSum);

				rigidbodyA.velocity += j * rigidbodyA.massInverse * intInfo.normal;
				rigidbodyB.velocity -= j * rigidbodyB.massInverse * intInfo.normal;
			}
		}
    }
}
