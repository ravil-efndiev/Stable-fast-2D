#include "Texture.hpp"
#include "Engine.hpp"
#include <stb_image.h>

namespace s2f
{
    Texture::Texture(const std::filesystem::path& texturePath, const std::optional<GLTextureSettingsCallback>& settings)
    {
        create(texturePath, settings);
        Logger::infoVerbose("Created texture from file: \"{}\", valid = {}", texturePath.string(), mValid);
    }

    Texture::Texture(
        i32 width, i32 height, void* data, i32 numChannels, const std::optional<GLTextureSettingsCallback>& settings
    ) {
        create(width, height, data, numChannels, settings);
        Logger::infoVerbose("Created texture from data array, size = {}x{}, valid = {}", width, height, mValid);
    }

    Status Texture::create(
        const std::filesystem::path& texturePath, 
        const std::optional<GLTextureSettingsCallback>& settings
    ) {
        stbi_set_flip_vertically_on_load(true);

        i32 width, height;
        u8* data = stbi_load(texturePath.string().c_str(), &width, &height, &mNumChannels, 0);

        if (!data)
        {
            mValid = false;
            return statusError("Failed to load texture from file: " + texturePath.string());
        }

        Status status = create(width, height, data);
        stbi_image_free(data);

        if (!status.success)
            status.error = "File [" + texturePath.string() + "] " + status.error;

        return status;
    }

    Status Texture::create(
        i32 width,
        i32 height,
        void* data,
        i32 numChannels, const std::optional<GLTextureSettingsCallback>& settings
    ) {
        if (numChannels)
            mNumChannels = numChannels;

        mValid = false;
        mWidth = width;
        mHeight = height;

        GLenum dataFormat, internalFormat;
        switch (mNumChannels)
        {
        case 1:
            dataFormat = GL_RED;
			internalFormat = GL_R8;
            break;
        case 2:
            dataFormat = GL_RG;
            internalFormat = GL_RG8;
            break;
        case 3:
            dataFormat = GL_RGB;
			internalFormat = GL_RGB8;
            break;
        case 4:
			dataFormat = GL_RGBA;
            internalFormat = GL_RGBA8;
			break;
        default:
            return statusError(std::format("Unsupported texture format provided (channels = {})", numChannels));
        }

        u32 mipmapLevels = floor(log2(glm::max(mWidth, mHeight))) + 1;

        glCreateTextures(GL_TEXTURE_2D, 1, &mID);
        if (settings)
			settings.value()(mID);
        else
        {
            glTextureParameteri(mID, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(mID, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTextureParameteri(mID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTextureParameteri(mID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }

        glTextureStorage2D(mID, mipmapLevels, internalFormat, mWidth, mHeight);

        if (data)
        {
            glTextureSubImage2D(mID, 0, 0, 0, mWidth, mHeight, dataFormat, GL_UNSIGNED_BYTE, data);
            glGenerateTextureMipmap(mID);
        }

        mValid = true;
        return statusSuccess();
    }

    void Texture::destroy()
    {
        glDeleteTextures(1, &mID);
        Logger::infoVerbose("Deleted texture with ID {}", mID);
        mValid = false;
        mWidth = 0;
        mHeight = 0;
        mNumChannels = 3;
    }

    Texture::~Texture()
    {
        Engine::get()->renderer().glState().invalidateTexture(mID);
        destroy();
    }
}
