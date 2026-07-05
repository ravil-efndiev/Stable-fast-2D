#pragma once
#include "api/ECS/DefaultComponents/defaultComponents.hpp"
#include "api/ECS/Entity.hpp"

namespace s2f
{
	/*
	* @brief Default system that updates sub texture data of entities that have a Sprite component
	* depending on animation data of SpriteAnimator component
	* @param entities list of entities in a scene
	* @param deltaTime time difference between frames, also accessible via Time::delta()
	*/
	void spriteAnimationSystem(const std::vector<Entity>& entities, f32 deltaTime);

	/*
	* @brief Default system that updates particle positions, rotations and lifetimes
	* for ParticleEmitter components
	* @param entities list of entities in a scene
	* @param deltaTime time difference between frames, also accessible via Time::delta()
	*/
	void particleSystem(const std::vector<Entity>& entities, f32 deltaTime);

	/*
	* @brief Default system that updates collider bounds to match Transform position
	* 
	* Works for Collider and ColliderList components
	* @param entities list of entities in a scene
	* @param deltaTime time difference between frames, also accessible via Time::delta()
	*/
	void colliderPositionSystem(const std::vector<Entity>& entities, f32 deltaTime);

	/*
	* @brief Default system running in fixed timestep that updates velocity for RigidBody
	* and position for Transform based on velocities
	*
	* Works for Collider and ColliderList components
	* @param entities list of entities in a scene
	* @param fixedDeltaTime = 1/60 by default but may vary, provided by Engine, also
	* accessible via Time::fixedDelta()
	*/
	void rigidbodySystemF(const std::vector<Entity>& entities, f32 fixedDeltaTime);

	/*
	* @brief Default system that resolves collisions of rigid bodies with colliders
	* @param entities list of entities in a scene
	* @param deltaTime time difference between frames, also accessible via Time::delta()
	*/
	void rigidbodyCollisionSystem(const std::vector<Entity>& entities, f32 deltaTime);
}
