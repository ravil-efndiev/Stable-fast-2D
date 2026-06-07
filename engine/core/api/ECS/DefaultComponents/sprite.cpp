#include "sprite.hpp"

#define CHECK_TEXTURE_VALID \
	if (!texture || (texture && !texture->valid())) { \
		Logger::warn("Trying to set subtexture to a sprite that doesn't have initialized or valid texture"); \
		return; \
	}

namespace s2f
{
	Sprite::Sprite()
	{
		texture = std::make_shared<Texture>();
	}

	Sprite::Sprite(const glm::vec4& color) : color(color)
	{
		texture = std::make_shared<Texture>();
	}

	Sprite::Sprite(const std::filesystem::path& texturePath, const glm::vec4& color) 
		: color(color)
	{
		texture = std::make_shared<Texture>();
		texture->create(texturePath);
	}

	void Sprite::setSubTexture(const glm::uvec2& position, const glm::uvec2& size)
	{
		CHECK_TEXTURE_VALID;
		subTexture = SubTexture(texture->size(), position, size);
	}

	void Sprite::setSubTextureFromGrid(const glm::uvec2& gridCoords, const glm::uvec2& size)
	{
		CHECK_TEXTURE_VALID;
		subTexture = SubTexture::fromGrid(texture->size(), gridCoords, size);
	}
}
