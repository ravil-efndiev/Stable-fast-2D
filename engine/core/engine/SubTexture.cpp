#include "SubTexture.hpp"

namespace s2f
{
	SubTexture::SubTexture(const glm::ivec2& baseTextureSize, const glm::uvec2& position, const glm::uvec2& size)
		: mBaseTextureSize(baseTextureSize), mPosition(position), mSize(size) 
	{
		calculateCoords();
	}

	SubTexture SubTexture::fromGrid(const glm::ivec2& baseTextureSize, const glm::uvec2& gridCoords, const glm::uvec2& size)
	{
		return SubTexture(baseTextureSize, gridCoords * size, size);
	}

	void SubTexture::setPosition(const glm::uvec2& position)
	{
		mPosition = position;
		calculateCoords();
	}

	void SubTexture::setSize(const glm::uvec2& size)
	{
		mSize = size;
		calculateCoords();
	}

	void SubTexture::calculateCoords()
	{
		f32 minX = (f32)mPosition.x / (f32)mBaseTextureSize.x;
		f32 maxX = (f32)(mPosition.x + mSize.x) / (f32)mBaseTextureSize.x;

		f32 minY = 1.f - (f32)(mPosition.y + mSize.y) / (f32)mBaseTextureSize.y;
		f32 maxY = 1.f - (f32)(mPosition.y) / (f32)mBaseTextureSize.y;

		mTextureCoords[0] = { minX, maxY };
		mTextureCoords[1] = { maxX, maxY };
		mTextureCoords[2] = { maxX, minY };
		mTextureCoords[3] = { minX, minY };
	}

	bool SubTexture::valid() const
	{
		return mSize.x > 0 &&
			mSize.y > 0 &&
			mBaseTextureSize.x > 0 &&
			mBaseTextureSize.y > 0;
	}
}
