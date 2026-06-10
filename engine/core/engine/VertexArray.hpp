#pragma once
#include "Buffer.hpp"
#include "layout.hpp"

namespace s2f
{
	enum class Divisor : u32
	{
		PerVertex = 0,
		PerInstnace = 1,
	};

	class VertexArray
	{
	public:
		VertexArray() = default;
		~VertexArray();

		void create();
	
		void addVertexBuffer(const Buffer& vertexBuffer, const Layout& layout, Divisor divisor);
		void setIndexBuffer(const Buffer& indexBuffer);

		GLuint id() const { return mID; }
		u64 indexBufferIndexCount() const { return mIndexBufferIndexCount; }

	private:
		u64 mIndexBufferIndexCount{ 0 };
		GLuint mID{ 0 };
		u32 mCurrentAttribIndex{ 0 };
	};
}
