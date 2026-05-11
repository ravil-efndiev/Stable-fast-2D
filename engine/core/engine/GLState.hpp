#pragma once
#include "include.hpp"
#include "VertexArray.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"

namespace s2f
{
	struct GLState
	{
		GLuint activeVA{ 0 };
		GLuint activeVB{ 0 };
		GLuint activeIB{ 0 };
		GLuint activeShader{ 0 };

		void bindVA(const VertexArray& va);
		void bindBuffer(const Buffer& vb);
		void bindShader(const Shader& shader);
	};
}
