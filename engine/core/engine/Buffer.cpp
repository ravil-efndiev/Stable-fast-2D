#include "Buffer.hpp"

namespace s2f
{
	Buffer::Buffer(BufferType type, u64 elementCount, u64 size, void* data)
	{
		create(type, elementCount, size, data);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &mID);
		Logger::infoVerbose("Deleted buffer with ID {}", mID);
	}

	void Buffer::create(BufferType type, u64 elementCount, u64 size, void* data)
	{
		mType = type;
		mElementCount = elementCount;
		S2F_ASSERT(mType != BufferType::Uninitialized,
			"Buffer type must be specified when creating a buffer");
		glCreateBuffers(1, &mID);
		glNamedBufferData(mID, size, data, GL_DYNAMIC_DRAW);
		Logger::infoVerbose("Created buffer with ID {}, size = {}", mID, size);
	}

	void Buffer::setData(u64 size, void* data) const
	{
		S2F_ASSERT(valid(), "Attempted to set data for an empty or invalid buffer");
		glNamedBufferSubData(mID, 0, size, data);
	}

    void Buffer::realloc(u64 size) const
    {
		S2F_ASSERT(valid(), "Attempted to realloc an empty or invalid buffer");
		glNamedBufferData(mID, size, nullptr, GL_DYNAMIC_DRAW);
    }

    bool Buffer::valid() const
	{
		return mType != BufferType::Uninitialized;
	}
}
