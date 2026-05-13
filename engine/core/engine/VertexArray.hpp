#pragma once
#include "Buffer.hpp"
#include "layout.hpp"

namespace s2f
{
	class VertexArray
	{
	public:
		VertexArray() = default;
		~VertexArray();

		void create();
	
		void setVertexBuffer(const Buffer& vertexBuffer, const Layout& layout);
		void setIndexBuffer(const Buffer& indexBuffer);

		GLuint id() const { return mID; }

	private:
		GLuint mID{ 0 };
		u32 mCurrentAttribIndex{ 0 };
	};
}
