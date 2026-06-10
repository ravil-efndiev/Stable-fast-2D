#pragma once
#include "include.hpp"

namespace s2f
{
	enum class BufferType : u8
	{
		Uninitialized = 0, Vertex, Index
	};

	class Buffer
	{
	public:
		Buffer() = default;
		Buffer(BufferType type, u64 elementCount, u64 size, void* data = nullptr);
		~Buffer();

		void create(BufferType type, u64 elementCount, u64 size, void* data = nullptr);

		GLuint id() const { return mID; }
		BufferType type() const { return mType; }
		u32 elementCount() const { return mElementCount; }

		bool valid() const;
		void setData(u64 size, void* data) const;
		void realloc(u64 size) const;

	private:
		GLuint mID{ 0 };
		BufferType mType{ BufferType::Uninitialized };
		u64 mElementCount{ 0 };
	};
}
