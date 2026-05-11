#include "Buffer.hpp"

namespace s2f
{
	void Buffer::create(void* data, size_t size)
	{
		glCreateBuffers(1, &mID);
		glNamedBufferData(mID, size, data, GL_STATIC_DRAW);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &mId);
	}

	GLuint Buffer::id() const
	{
		return mID;
	}

	BufferType Buffer::type() const
	{
		return mType;
	}
}
