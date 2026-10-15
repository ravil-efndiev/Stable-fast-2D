#pragma once
#include "Renderer.hpp"

namespace s2f 
{
	struct CharacterData
	{
		glm::uvec2 subtexturePosition;
		glm::uvec2 bmpSize;
		glm::uvec2 bmpBearing;
		u32 advance;
	};

	using CharacterDataArray = std::array<CharacterData, 128>;

	struct Font
	{
		std::shared_ptr<Texture> atlasTexture;
		CharacterDataArray charactersData;
	};

	class TextRenderer
	{
	public:
		TextRenderer(Renderer& renderer);
		~TextRenderer();

		Status addFont(
			std::string_view fontName,
			const std::filesystem::path& fontPath
		);

		Status drawString(
			std::string_view text,
			const glm::mat4& transform,
			const glm::vec4& color = glm::vec4(1.f),
			const std::string& fontName = "default"
		);

	private:
		glm::uvec2 getAtlasSize() const;
		std::pair<CharacterDataArray, std::vector<u8>> generateGlyphBytesAndMetadata(const glm::uvec2& size) const;

	private:
		std::unordered_map<std::string, Font> mFonts;
		FT_Library mFreetype{ nullptr };
		FT_Face mFace{ nullptr };

		Renderer& mRenderer;
		bool mValid{ false };
	};
}
