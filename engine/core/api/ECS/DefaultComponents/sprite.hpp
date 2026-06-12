#pragma once
#include "engine/Texture.hpp"
#include "engine/SubTexture.hpp"

namespace s2f
{
	struct Sprite
	{
		std::shared_ptr<Texture> texture;
		SubTexture subTexture;
		glm::vec4 color{ 1.f };

		Sprite(const glm::vec4& color);
		Sprite(const std::filesystem::path& texturePath, const glm::vec4& color = glm::vec4(1.f));

		void setSubTexture(const glm::uvec2& position, const glm::uvec2& size);
		void setSubTextureFromGrid(const glm::uvec2& gridCoords, const glm::uvec2& size);
	};
}
