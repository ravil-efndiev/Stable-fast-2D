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
		Buffer(BufferType type, size_t size, void* data = nullptr);
		~Buffer();

		void create(BufferType type, size_t size, void* data = nullptr);

		GLuint id() const { return mID; }
		BufferType type() const { return mType; }

		bool valid() const;
		void setData(size_t size, void* data) const;

	private:
		GLuint mID{ 0 };
		BufferType mType{ BufferType::Uninitialized };
	};
}
