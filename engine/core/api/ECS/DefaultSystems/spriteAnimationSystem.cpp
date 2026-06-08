#include "defaultSystems.hpp"
#include "api/ECS/entityQuery.hpp"

namespace s2f
{
	void spriteAnimationSystem(const std::vector<Entity>& entities, f32 dt)
	{
		auto queried = queryEntities<Sprite, SpriteAnimator>(entities);
		for (auto&& [entity, sprite, animator] : queried)
		{
			if (animator.animations.empty()) continue;
			if (animator.currentAnimationFinished()) continue;

			RectU gridCell = animator.currentAnimation()->subtextureGridCell();
			sprite.setSubTextureFromGrid(gridCell.position, gridCell.size);
		}
	}
}
