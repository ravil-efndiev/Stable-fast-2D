#include "defaultSystems.hpp"

namespace s2f
{
	void spriteAnimationSystem(const std::vector<Entity>& entities, f32 dt)
	{
		for (const auto& entity : entities)
		{
			if (!entity.has<Sprite>() || !entity.has<SpriteAnimator>()) return;

			auto& sprite = *entity.get<Sprite>();
			auto& animator = *entity.get<SpriteAnimator>();

			if (animator.animations.empty()) return;
			if (animator.currentAnimationFinished()) return;

			RectU gridCell = animator.currentAnimation()->subtextureGridCell();
			sprite.setSubTextureFromGrid(gridCell.position, gridCell.size);
		}
	}
}
