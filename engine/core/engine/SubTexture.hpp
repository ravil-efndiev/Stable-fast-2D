#pragma once
#include "Texture.hpp"

namespace s2f
{
	class SubTexture
	{
	public:
		SubTexture() = default;
		SubTexture(const glm::ivec2& baseTextureSize, const glm::uvec2& position, const glm::uvec2& size);

		static SubTexture fromGrid(const glm::ivec2& baseTextureSize, const glm::uvec2& gridCoords, const glm::uvec2& size);

		void setPosition(const glm::uvec2& position);
		void setSize(const glm::uvec2& size);

		glm::uvec2 position() const { return mPosition; }
		glm::uvec2 size() const { return mSize; }

		std::array<glm::vec2, 4> textureCoords() const { return mTextureCoords; }

		bool valid() const;

	private:
		void calculateCoords();

	private:
		glm::uvec2 mPosition{ 0 };
		glm::uvec2 mSize{ 0 };

		glm::ivec2 mBaseTextureSize{ 0 };
		std::array<glm::vec2, 4> mTextureCoords{};
	};
}
