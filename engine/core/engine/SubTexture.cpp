#include "SubTexture.hpp"

namespace s2f
{
	SubTexture::SubTexture(const glm::ivec2& baseTextureSize, const glm::uvec2& gridPosition, const glm::uvec2& size)
		: mBaseTextureSize(baseTextureSize), mGridPosition(gridPosition), mSize(size) 
	{
		calculateCoords();
	}

	void SubTexture::setGridPosition(const glm::uvec2 gridPosition)
	{
		mGridPosition = gridPosition;
		calculateCoords();
	}

	void SubTexture::setSize(const glm::uvec2 size)
	{
		mSize = size;
		calculateCoords();
	}

	void SubTexture::calculateCoords()
	{
		f32 minX = (f32)(mGridPosition.x * mSize.x) / (f32)mBaseTextureSize.x;
		f32 maxX = (f32)((mGridPosition.x + 1) * mSize.x) / (f32)mBaseTextureSize.x;

		f32 minY = 1.f - (f32)((mGridPosition.y + 1) * mSize.y) / (f32)mBaseTextureSize.y;
		f32 maxY = 1.f - (f32)(mGridPosition.y * mSize.y) / (f32)mBaseTextureSize.y;

		glm::vec2 min{ minX, minY };
		glm::vec2 max{ maxX, maxY };

		mTextureCoords[0] = { min.x, max.y };
		mTextureCoords[1] = { max.x, max.y };
		mTextureCoords[2] = { max.x, min.y };
		mTextureCoords[3] = { min.x, min.y };
	}

	bool SubTexture::valid() const
	{
		return mSize.x > 0 &&
			mSize.y > 0 &&
			mBaseTextureSize.x > 0 &&
			mBaseTextureSize.y > 0;
	}
}
