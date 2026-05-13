#include "GLState.hpp"
#include "GLAPI.hpp"

namespace s2f
{
    GLState::GLState()
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
		if (activeTextures[textureSlot] == id || !texture.valid()) return;

		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, id);
		activeTextures[textureSlot] = id;
    }
}
