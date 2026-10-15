#pragma once
#include "include.hpp"
#include "status.hpp"

namespace s2f
{
	using GLTextureSettingsCallback = std::function<void(GLuint)>;

    class Texture
    {
    public:
        Texture() = default;
        Texture(
            const std::filesystem::path& texturePath, const std::optional<GLTextureSettingsCallback>& settings = std::nullopt
        );
        Texture(
            i32 width, i32 height, void* data, i32 numChannels, const std::optional<GLTextureSettingsCallback>& settings = std::nullopt
        );
        ~Texture();

        Status create(
            const std::filesystem::path& texturePath, const std::optional<GLTextureSettingsCallback>& settings = std::nullopt
        );
        Status create(
            i32 width, i32 height, void* data, i32 numChannels = 0, const std::optional<GLTextureSettingsCallback>& settings = std::nullopt
        );
        void destroy();

        GLuint id() const { return mID; }
        glm::ivec2 size() const { return { mWidth, mHeight }; }
        bool valid() const { return mValid; }

    private:
        GLuint mID{ 0 };
        i32 mWidth{ 0 };
        i32 mHeight{ 0 };
        i32 mNumChannels{ 3 };
        bool mValid{ false };
    };
}
