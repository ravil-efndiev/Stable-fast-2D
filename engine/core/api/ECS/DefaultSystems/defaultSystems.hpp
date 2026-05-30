#pragma once
#include "api/ECS/DefaultComponents/sprite.hpp"
#include "api/ECS/DefaultComponents/spriteAnimator.hpp"
#include "api/ECS/Entity.hpp"

namespace s2f
{
	void spriteAnimationSystem(const std::vector<Entity>& entities, f32 dt);
}
