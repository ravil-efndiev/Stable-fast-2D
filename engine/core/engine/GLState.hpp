#pragma once
#include "include.hpp"
#include "VertexArray.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace s2f
{
	struct GLState
	{
		GLuint activeVA{ 0 };
		GLuint activeShader{ 0 };
		std::vector<GLuint> activeTextures;

		void init();

		void bindVA(const VertexArray& va);
		void bindShader(const Shader& shader);
		void bindTexture(const Texture& texture, u32 textureSlot);
	};
}
