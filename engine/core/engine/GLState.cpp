#include "GLState.hpp"
#include "GLAPI.hpp"

namespace s2f
{
    void GLState::init()
    {
		auto maxTextureSlots = glapi::getMaxTextureSlots();
		activeTextures.resize(maxTextureSlots);
    }

    void GLState::bindVA(const VertexArray& va)
	{
		GLuint id = va.id();
		if (activeVA == id) return;

		glBindVertexArray(id);
		activeVA = id;
	}

	void GLState::bindShader(const Shader& shader)
	{
		GLuint id = shader.id();
		if (activeShader == id || !shader.valid()) return;

		glUseProgram(id);
		activeShader = id;
	}

    void GLState::bindTexture(const Texture &texture, u32 textureSlot)
    {
		GLuint id = texture.id();
		if (!texture.valid())
		{
			S2F_ERROR("Attempted to bind an invalid texture to slot " << textureSlot);
			return;
		}
		if (activeTextures[textureSlot] == id) return;

		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, id);
		activeTextures[textureSlot] = id;
    }
}
