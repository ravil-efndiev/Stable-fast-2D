#include "GLState.hpp"

namespace s2f
{
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
}
