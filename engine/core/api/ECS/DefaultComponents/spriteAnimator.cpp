#include "spriteAnimator.hpp"
#include "engine/time.hpp"

namespace s2f
{
	SpriteAnimation::SpriteAnimation(const SpriteAnimationInfo& animationInfo)
		: mInfo(animationInfo)
	{
		mSubtextureGridCell =
		{
			{ mInfo.startXIdx, mInfo.startYIdx}, 
			mInfo.subTextureSize
		};
	}

	void SpriteAnimation::play()
	{
		mFinished = false;
		mTimer += 100.f * Time::delta();
		if (mTimer >= mInfo.frameTime)
		{
			mTimer = 0;
			if (mFrameIndex >= mInfo.endXIdx)
			{
				mFinished = true;
				mFrameIndex = mInfo.startXIdx;
			}
			else
			{
				mFrameIndex++;
			}

			mSubtextureGridCell.position.x = mFrameIndex;
		}
	}

	void SpriteAnimator::addAnimation(std::string_view name, const SpriteAnimationInfo& animationInfo)
	{
		animations.emplace(name, SpriteAnimation(animationInfo));
		if (mCurrentAnimationName.empty())
			mCurrentAnimationName = name;
	}

	void SpriteAnimator::playAnimation(const std::string& name)
	{
		auto it = animations.find(name);
		if (it == animations.end())
		{
			Logger::error("SpriteAnimator::playAnimation() animation with name \"{}\" doesn't exist", name);
			return;
		}

		auto& anim = it->second;
		anim.play();

		if (mCurrentAnimationName != name)
			mCurrentAnimationName = name;
	}

	const SpriteAnimation* SpriteAnimator::currentAnimation() const
	{
		if (!mCurrentAnimationName.empty())
			return &animations.at(mCurrentAnimationName);
		Logger::error("SpriteAnimator::currentAnimation() SpriteAnimator component has no animations");
		return nullptr;
	}

	bool SpriteAnimator::currentAnimationFinished() const
	{
		auto* currentAnim = currentAnimation();
		if (!currentAnim) return true;
		return currentAnim->finished();
	}
}
