#pragma once
#include "engine/Texture.hpp"

namespace s2f
{
	struct Sprite
	{
		std::shared_ptr<Texture> texture;
		glm::vec4 color{ 1.f };

		Sprite() : texture(std::make_shared<Texture>()) {}
		Sprite(const glm::vec4& color) 
			: texture(std::make_shared<Texture>()), color(color) {}
		Sprite(const std::filesystem::path& texturePath, const glm::vec4& color = glm::vec4(1.f))
			: texture(std::make_shared<Texture>()), color(color) 
		{
			texture->create(texturePath);
		}

	};
}
