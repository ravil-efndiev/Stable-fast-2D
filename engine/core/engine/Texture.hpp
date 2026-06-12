#pragma once
#include "include.hpp"
#include "status.hpp"

namespace s2f
{
    class Texture
    {
    public:
        Texture() = default;
        Texture(const std::filesystem::path& texturePath);
        Texture(i32 width, i32 height, void* data);
        ~Texture();

        Status create(const std::filesystem::path& texturePath);
        Status create(i32 width, i32 height, void* data);
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
