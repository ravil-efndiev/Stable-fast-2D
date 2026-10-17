#pragma once
#include "include.hpp"
#include "status.hpp"
#include "GLAPI.hpp"

namespace s2f
{
    using DefaultCallbackT = decltype(glapi::callbacks::defaultTextureSettings);

    class Texture
    {
    public:
        Texture() = default;

		template<class Func = DefaultCallbackT> requires Callback<Func, GLuint>
        Texture(
            const std::filesystem::path& texturePath, Func&& settings = glapi::callbacks::defaultTextureSettings
        );

        template<class Func = DefaultCallbackT> requires Callback<Func, GLuint>
        Texture(
            i32 width, i32 height, void* data, i32 numChannels, Func&& settings = glapi::callbacks::defaultTextureSettings
        );
        ~Texture();

        template<class Func = DefaultCallbackT> requires Callback<Func, GLuint>
        Status create(
            const std::filesystem::path& texturePath, Func&& settings = glapi::callbacks::defaultTextureSettings
        );

        template<class Func = DefaultCallbackT> requires Callback<Func, GLuint>
        Status create(
            i32 width, i32 height, void* data, i32 numChannels = 0, Func&& settings = glapi::callbacks::defaultTextureSettings
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

#include "Texture.inl"