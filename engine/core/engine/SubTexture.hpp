#pragma once
#include "Texture.hpp"

namespace s2f
{
	class SubTexture
	{
	public:
		SubTexture() = default;
		SubTexture(const glm::ivec2& baseTextureSize, const glm::uvec2& gridPosition, const glm::uvec2& size);

		void setGridPosition(const glm::uvec2 gridPosition);
		void setSize(const glm::uvec2 size);

		glm::uvec2 gridPosition() const { return mGridPosition; }
		glm::uvec2 size() const { return mSize; }

		std::array<glm::vec2, 4> textureCoords() const { return mTextureCoords; }

		bool valid() const;

	private:
		void calculateCoords();

	private:
		glm::uvec2 mGridPosition{ 0 };
		glm::uvec2 mSize{ 0 };

		glm::ivec2 mBaseTextureSize{ 0 };
		std::array<glm::vec2, 4> mTextureCoords{};
	};
}
