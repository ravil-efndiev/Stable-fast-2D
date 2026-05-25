#include "sprite.hpp"

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

	void Sprite::setSubTexture(const glm::uvec2& gridPosition, const glm::uvec2& size)
	{
		if (!texture || (texture && !texture->valid()))
		{
			log::warn("Trying to set subtexture to a sprite that doesn't have initialized or valid texture");
			return;
		}

		subTexture = SubTexture(texture->size(), gridPosition, size);
	}
}
