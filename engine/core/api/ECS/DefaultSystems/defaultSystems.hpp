#pragma once
#include "api/ECS/DefaultComponents/sprite.hpp"
#include "api/ECS/DefaultComponents/spriteAnimator.hpp"
#include "api/ECS/DefaultComponents/particleEmitter.hpp"
#include "api/ECS/Entity.hpp"

namespace s2f
{
	/*
	* @brief Default system that updates sub texture data of entities that have a Sprite component
	* depending on animation data of SpriteAnimator component
	* 
	* @param entities list of entities in a scene
	* @param deltaTime time difference between frames, also accessible via Time::delta()
	*/
	void spriteAnimationSystem(const std::vector<Entity>& entities, f32 deltaTime);

	void particleSystem(const std::vector<Entity>& entities, f32 deltaTime);

}
