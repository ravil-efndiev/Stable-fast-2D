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

    void rigidbodySystem(const std::vector<Entity>& entities, f32 deltaTime)
    {
		for (auto&& [transform, rigidbody] : queryComponents<Transform, Rigidbody>(entities))
		{
			glm::vec2 acceleration = rigidbody.forces * rigidbody.massInverse;
			rigidbody.velocity += acceleration * deltaTime;
			transform.position += glm::vec3(rigidbody.velocity, 0.f) * deltaTime;
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
				if (intersect(colliderA.bounds, colliderB.bounds))
				{
					// TODO learn physics
				}				
			}
		}
    }
}
