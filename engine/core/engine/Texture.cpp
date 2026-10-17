#include "Texture.hpp"
#include "Engine.hpp"
#include <stb_image.h>

namespace s2f
{
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
