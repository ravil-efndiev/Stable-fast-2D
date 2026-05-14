#include "VertexArray.hpp"

namespace s2f
{
	void VertexArray::create()
	{
		glCreateVertexArrays(1, &mID);
		S2F_INFO("Created vertex array with ID " << mID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &mID);
		S2F_INFO("Deleted vertex array with ID " << mID);
	}

	void VertexArray::setVertexBuffer(const Buffer& vertexBuffer, const Layout& layout)
	{
		S2F_ASSERT(vertexBuffer.type() == BufferType::Vertex, 
			"Buffer passed to setVertexBuffer must be of type Vertex");

		S2F_ASSERT(vertexBuffer.valid(), "Attempted to set an invalid or empty vertex buffer for a vertex array");

		glBindVertexArray(mID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.id());
		for (const auto& element : layout.elements)
		{
			if (element.type == LayoutElementType::Float4x4)
			{
				i32 vec4Count = getLayoutElementComponentCount(element.type);
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
				i32 floatCount = getLayoutElementComponentCount(element.type);
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

	void VertexArray::setIndexBuffer(const Buffer& indexBuffer)
	{
		S2F_ASSERT(indexBuffer.type() == BufferType::Index,
			"Buffer passed to setIndexBuffer must be of type Index");

		S2F_ASSERT(indexBuffer.valid(), "Attempted to set an invalid or empty index buffer for a vertex array");

		glBindVertexArray(mID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.id());
	}
}
