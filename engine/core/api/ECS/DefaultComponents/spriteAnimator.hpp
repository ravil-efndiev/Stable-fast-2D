#pragma once
#include "include.hpp"
#include "api/math/Rect.hpp"

namespace s2f
{
	struct SpriteAnimationInfo
	{
		f32 frameTime;
		u32 startXIdx, startYIdx, endXIdx;
		glm::uvec2 subTextureSize;
	};

	class SpriteAnimation
	{
	public:
		explicit SpriteAnimation(const SpriteAnimationInfo& animationInfo);

		SpriteAnimationInfo info() const { return mInfo; }

		void play();
		RectU subtextureGridCell() const { return mSubtextureGridCell; }
		bool finished() const { return mFinished; }

	private:
		SpriteAnimationInfo mInfo;

		u32 mFrameIndex{ 0 };
		RectU mSubtextureGridCell{};
		f32 mTimer{ 0.f };
		bool mFinished{ false };
	};

	class SpriteAnimator
	{
	public:
		std::unordered_map<std::string, SpriteAnimation> animations;

		void addAnimation(std::string_view name, const SpriteAnimationInfo& animationInfo);
		void playAnimation(const std::string& name);
		const SpriteAnimation* currentAnimation() const;
		bool currentAnimationFinished() const;

	private:
		std::string mCurrentAnimationName{};
	};
}
