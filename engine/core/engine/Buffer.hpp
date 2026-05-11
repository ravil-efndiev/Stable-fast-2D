#pragma once
#include "include.hpp"

namespace s2f
{
	enum class BufferType
	{
		Vertex, Index
	};

	class Buffer
	{
	public:
		template <class T>
		Buffer(BufferType type, const std::vector<T>& data)
			: mType(type)
		{
			create(data.data(), data.size() * sizeof(T));
		}
		~Buffer();

		GLuint id() const;
		BufferType type() const;

	private:
		void create(void* data, size_t size);

	private:
		GLuint mID{ 0 };
		BufferType mType;
	};
}
