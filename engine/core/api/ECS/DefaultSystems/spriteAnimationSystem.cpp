#include "defaultSystems.hpp"
#include "api/ECS/entityQuery.hpp"

namespace s2f
{
	void spriteAnimationSystem(const std::vector<Entity>& entities, f32 dt)
	{
		for (auto&& [sprite, animator] : queryComponents<Sprite, SpriteAnimator>(entities))
		{
			if (animator.animations.empty()) continue;
			if (animator.currentAnimationFinished()) continue;

			RectU gridCell = animator.currentAnimation()->subtextureGridCell();
			sprite.setSubTextureFromGrid(gridCell.position, gridCell.size);
		}
	}
}
