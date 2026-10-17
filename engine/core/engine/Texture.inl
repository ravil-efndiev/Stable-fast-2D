#include "include.hpp"
#include "status.hpp"
#include <stb_image.h>

namespace s2f
{
    template<class Func> requires Callback<Func, GLuint>
    Texture::Texture(const std::filesystem::path& texturePath, Func&& settings)
    {
        create(texturePath, settings);
        Logger::infoVerbose("Created texture from file: \"{}\", valid = {}", texturePath.string(), mValid);
    }

    template<class Func> requires Callback<Func, GLuint>
    Texture::Texture(
        i32 width, i32 height, void* data, i32 numChannels, Func&& settings
    ) {
        create(width, height, data, numChannels, settings);
        Logger::infoVerbose("Created texture from data array, size = {}x{}, valid = {}", width, height, mValid);
    }

    template<class Func> requires Callback<Func, GLuint>
    Status Texture::create(
        const std::filesystem::path& texturePath,
        Func&& settings
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

    template<class Func> requires Callback<Func, GLuint>
    Status Texture::create(
        i32 width,
        i32 height,
        void* data,
        i32 numChannels,
        Func&& settings
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
        settings(mID);

        glTextureStorage2D(mID, mipmapLevels, internalFormat, mWidth, mHeight);

        if (data)
        {
            glTextureSubImage2D(mID, 0, 0, 0, mWidth, mHeight, dataFormat, GL_UNSIGNED_BYTE, data);
            glGenerateTextureMipmap(mID);
        }

        mValid = true;
        return statusSuccess();
    }
}
