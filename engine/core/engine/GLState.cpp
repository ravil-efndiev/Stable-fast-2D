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

	void GLState::bindBuffer(const Buffer& buffer)
	{
		GLuint id = buffer.id();
		BufferType type = buffer.type();

		if (type == BufferType::Vertex) 
		{
			if (activeVB == id) return;
			glBindBuffer(GL_ARRAY_BUFFER, id);
			activeVB = id;
		}
		else if (type == BufferType::Index)
		{
			if (activeIB == id) return;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			activeIB = id;
		}
	}

	void GLState::bindShader(const Shader& shader)
	{
		GLuint id = shader.id();
		if (activeShader == id) return;

		glUseProgram(id);
		activeShader = id;
	}
}
