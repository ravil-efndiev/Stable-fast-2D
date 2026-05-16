#include "Texture.hpp"
#include <stb_image.h>

namespace s2f
{
    Status Texture::create(const std::filesystem::path& texturePath)
    {
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

		S2F_INFO_VERBOSE("Created texture from file: " << texturePath.string() << ", valid = " << mValid);
        return status;
    }

    Status Texture::create(i32 width, i32 height, void* data)
    {
        mValid = false;
        mWidth = width;
        mHeight = height;

        GLenum dataFormat = (mNumChannels == 3) ? GL_RGB : GL_RGBA;
        GLenum internalFormat = (mNumChannels == 3) ? GL_RGB8 : GL_RGBA8;
        u32 mipmapLevels = floor(log2(glm::max(mWidth, mHeight))) + 1;

        glCreateTextures(GL_TEXTURE_2D, 1, &mID);
        glTextureParameteri(mID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(mID, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureParameteri(mID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(mID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureStorage2D(mID, mipmapLevels, internalFormat, mWidth, mHeight);

        if (data)
        {
            glTextureSubImage2D(mID, 0, 0, 0, mWidth, mHeight, dataFormat, GL_UNSIGNED_BYTE, data);
            glGenerateTextureMipmap(mID);
        }

        mValid = true;
        return statusSuccess();
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &mID);
		S2F_INFO_VERBOSE("Deleted texture with ID " << mID);
    }
}
