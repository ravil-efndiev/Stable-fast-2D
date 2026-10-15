#include "TextRenderer.hpp"

namespace s2f
{
	static void fontTextureSettings(GLuint texId)
	{
		glTextureParameteri(texId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(texId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(texId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(texId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	TextRenderer::TextRenderer(Renderer& renderer)
		: mRenderer(renderer)
	{
		FT_Error initErr = FT_Init_FreeType(&mFreetype);
		if (initErr)
		{
			Logger::error("TextRenderer: Failed to initialize Freetype");
			return;
		}
		mValid = true;

		checkStatuses(addFont("default", ASSETS_PATH / "fonts" / "arial.ttf"));
	}

	TextRenderer::~TextRenderer()
	{
		FT_Done_FreeType(mFreetype);
	}

	Status TextRenderer::addFont(std::string_view fontName, const std::filesystem::path& fontPath) 
	{
		FT_Error faceErr = FT_New_Face(mFreetype, fontPath.string().c_str(), 0, &mFace);
		if (faceErr)
		{
			return statusError("TextRenderer: Failed to create a face for a font");
		}

		FT_Error psError = FT_Set_Pixel_Sizes(mFace, 0, 48);
		if (psError)
		{
			return statusError("TextRenderer: Failed to set pixel sizes for a font");
		}

		try
		{
			auto atlasSize = getAtlasSize();
			auto [metaArr, data] = generateGlyphBytesAndMetadata(atlasSize);

			FT_Done_Face(mFace);
			mFace = nullptr;

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			Font font{ 
				std::make_shared<Texture>(
					atlasSize.x,
					atlasSize.y,
					data.data(),
					1,
					fontTextureSettings
				),
				std::move(metaArr)
			};

			auto [_, inserted] = mFonts.emplace(fontName, std::move(font));
			if (!inserted)
				return statusError(std::format("TextRenderer: Font with name \"{}\" already exists", fontName));

			return statusSuccess();
		} 
		catch (const std::exception& ex)
		{
			return statusError(ex.what());
		}
	}

	Status TextRenderer::drawString(
		std::string_view text,
		const glm::mat4& transform, 
		const glm::vec4& color, 
		const std::string& fontName
	) {
		auto it = mFonts.find(fontName);
		if (it == mFonts.end()) {
			return statusError(std::format("TextRenderer drawString(): no font with name \"{}\" found", fontName));
		}

		const Font& font = it->second;

		f32 cursorX = 0.0f;
		constexpr f32 baselineY = 0.0f;

		for (char c : text) 
		{
			CharacterData charData = font.charactersData[c];
			f32 centerX = cursorX + charData.bmpBearing.x + static_cast<f32>(charData.bmpSize.x) * 0.5f;
			f32 centerY = baselineY + charData.bmpBearing.y - static_cast<f32>(charData.bmpSize.y) * 0.5f;

			if (charData.bmpSize.x > 0 && charData.bmpSize.y > 0)
			{
				SubTexture glyphSubtexture(
					font.atlasTexture->size(),
					charData.subtexturePosition,
					charData.bmpSize
				);


				glm::mat4 glyphTransform = glm::translate(
					glm::mat4(1.0f),
					glm::vec3(centerX, centerY, 0.0f)
				);

				glyphTransform = glm::scale(
					glyphTransform,
					glm::vec3(
						static_cast<f32>(charData.bmpSize.x),
						static_cast<f32>(charData.bmpSize.y),
						1.0f
					)
				);

				mRenderer.drawQuad(
					transform * glyphTransform,
					font.atlasTexture.get(),
					glyphSubtexture,
					color,
					TextureType::RED
				);
				cursorX += charData.advance;
			}
		}

		return statusSuccess();
	}

	glm::uvec2 TextRenderer::getAtlasSize() const
	{
		glm::uvec2 atlasSize{};

		constexpr u32 padding{ 2 };

		for (u8 c{ 0 }; c < 128; c++)
		{
			FT_Error err = FT_Load_Char(mFace, c, FT_LOAD_RENDER);
			if (err)
				throw std::runtime_error("Text Renderer: couldn't load some data from given font file");

			atlasSize.x += mFace->glyph->bitmap.width;
			atlasSize.y = glm::max(atlasSize.y, mFace->glyph->bitmap.rows);

			if (c < 127)
				atlasSize.x += padding;
		}

		return atlasSize;
	}

	std::pair<CharacterDataArray, std::vector<u8>> TextRenderer::generateGlyphBytesAndMetadata(const glm::uvec2& size) const
	{
		std::vector<u8> data (size.x * size.y, 0);
		CharacterDataArray arr{};

		constexpr u32 padding{ 2 };
		u32 atlasX{ 0 };

		for (u8 c{ 0 }; c < 128; c++)
		{
			FT_Error err = FT_Load_Char(mFace, c, FT_LOAD_RENDER);
			if (err)
				throw std::runtime_error("Text Renderer: couldn't load some data from given font file");

			const auto& bitmap = mFace->glyph->bitmap;

			arr[c].bmpSize = { bitmap.width, bitmap.rows };
			arr[c].bmpBearing = { mFace->glyph->bitmap_left, mFace->glyph->bitmap_top };
			arr[c].advance = mFace->glyph->advance.x / 64.0f;
			arr[c].subtexturePosition = { atlasX, size.y - bitmap.rows };

			for (u32 row{ 0 }; row < bitmap.rows; row++)
			{
				u32 targetRow = bitmap.rows - 1 - row;

				for (u32 col{ 0 }; col < bitmap.width; col++)
				{
					data[static_cast<size_t>(targetRow * size.x + atlasX + col)] =
						bitmap.buffer[row * bitmap.pitch + col];
				}
			}

			atlasX += bitmap.width + padding;
		}

		return std::make_pair(arr, data);
	}
}
