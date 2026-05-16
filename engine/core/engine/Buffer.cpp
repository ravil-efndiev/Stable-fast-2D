#include "Buffer.hpp"

namespace s2f
{
	Buffer::Buffer(BufferType type, size_t size, void* data)
	{
		create(type, size, data);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &mID);
		S2F_INFO_VERBOSE("Deleted buffer with ID " << mID);
	}

	void Buffer::create(BufferType type, size_t size, void* data)
	{
		mType = type;
		S2F_ASSERT(mType != BufferType::Uninitialized,
			"Buffer type must be specified when creating a buffer");
		glCreateBuffers(1, &mID);
		glNamedBufferData(mID, size, data, GL_DYNAMIC_DRAW);
		S2F_INFO_VERBOSE("Created buffer with ID " << mID << ", size = " << size);
	}

	void Buffer::setData(size_t size, void* data) const
	{
		S2F_ASSERT(valid(), "Attempted to set data for an empty or invalid buffer");
		glNamedBufferSubData(mID, 0, size, data);
	}

	bool Buffer::valid() const
	{
		return mType != BufferType::Uninitialized;
	}
}
