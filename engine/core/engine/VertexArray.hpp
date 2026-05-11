#pragma once
#include "Buffer.hpp"
#include "layout.hpp"

namespace s2f
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
	
		void setVertexBuffer(const Buffer& vertexBuffer, const Layout& layout) const;

		GLuint id() const;

	private:
		GLuint mID{ 0 };
		u32 mCurrentAttribIndex{ 0 };
	};
}
