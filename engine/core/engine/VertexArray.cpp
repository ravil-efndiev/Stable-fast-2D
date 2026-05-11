#include "VertexArray.hpp"

namespace s2f
{
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &mID);
	}

	VertexArray::~VertexArray()
	{
		for (u32 i{ 0 }; i < mCurrentAttribIndex; i++)
			glDisableVertexAttribArray(i);
		glDeleteVertexArrays(1, &mID);
	}

	void VertexArray::setVertexBuffer(const Buffer& vertexBuffer, const Layout& layout) const
	{
		S2F_ASSERT(vertexBuffer.type() == BufferType::Vertex, 
			"Buffer passed to setVertexBuffer must be of type Vertex");

		glBindVertexArray(mID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.id());
		for (const auto& element : layout.elements)
		{
			if (element.type == LayoutElementType::Mat4)
			{
				i32 vec4Count = static_cast<i32>(element.type);
				for (i32 matVecIdx{ 0 }; matVecIdx < vec4Count; matVecIdx++)
				{
					glEnableVertexAttribArray(mCurrentAttribIndex);
					glVertexAttribPointer(
						mCurrentAttribIndex,
						vec4Count, GL_FLOAT,
						element.normalized,
						layout.stride,
						(void*)((uintptr_t)(element.offset + sizeof(f32) * vec4Count * matVecIdx))
					);
					mCurrentAttribIndex++;
				}
			}
			else
			{
				glEnableVertexAttribArray(mCurrentAttribIndex);
				i32 floatCount = static_cast<i32>(element.type);
				glVertexAttribPointer(
					mCurrentAttribIndex, 
					floatCount, GL_FLOAT,
					element.normalized,
					layout.stride, 
					(void*)((uintptr_t)element.offset)
				);
				mCurrentAttribIndex++;
			}
		}
	}

	GLuint VertexArray::id() const 
	{
		return mID;
	}
}
