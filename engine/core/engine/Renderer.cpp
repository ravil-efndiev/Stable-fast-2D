#include "Renderer.hpp"

namespace s2f
{
	Renderer::Renderer() 
		: mQuadBatchIndices(sQuadIndicesPerDraw)
	{
		mQuadVertexData.reserve(sQuadVerticesPerDraw);
	}

	void Renderer::init()
	{
		mQuadVA.create();
		mQuadVB.create(BufferType::Vertex, sQuadVerticesPerDraw * sizeof(meshes::QuadVertex));

		fillQuadBatchIndices();
		mQuadIB.create(BufferType::Index,
			sQuadIndicesPerDraw * sizeof(u32),
			mQuadBatchIndices.data()
		);

		mQuadVBLayout = Layout
		{
			{
				LayoutElement(LayoutElementType::Vec3, offsetof(meshes::QuadVertex, position)),
				LayoutElement(LayoutElementType::Vec4, offsetof(meshes::QuadVertex, tint)),
				LayoutElement(LayoutElementType::Vec2, offsetof(meshes::QuadVertex, texCoord)),
				LayoutElement(LayoutElementType::Float, offsetof(meshes::QuadVertex, texIndex))
			},
			sizeof(meshes::QuadVertex)
		};

		mQuadVA.setVertexBuffer(mQuadVB, mQuadVBLayout);
		mQuadVA.setIndexBuffer(mQuadIB);

		mQuadShader.create(SHADER_PATH / "quad.vert", SHADER_PATH / "quad.frag");
		auto maxTexSlots = glapi::getMaxTextureSlots();
		std::vector<i32> texSlotIndices(maxTexSlots);
		for (i32 i{ 0 }; i < maxTexSlots; i++)
			texSlotIndices[i] = i;

		mTextureSlots.resize(maxTexSlots);
		auto whiteTexData = 0xffffff;
		auto texStatus = mWhiteTexture.create(1, 1, &whiteTexData);
		S2F_INFO(texStatus.success);

		mTextureSlots[0] = mWhiteTexture.id();

		mQuadShader.setUniformIntArray("uTextureIndices", maxTexSlots, texSlotIndices.data(), &mGLState);
	}

	void Renderer::fillQuadBatchIndices()
	{
		size_t offset{ 0 };
		for (size_t i{ 0 }; i < sQuadIndicesPerDraw; i += 6)
		{
			for (size_t j{ 0 }; j < meshes::quadIndices.size(); j++)
			{
				mQuadBatchIndices[i + j] = offset + meshes::quadIndices[j];
			}
			offset += 4;
		}
	}

	void Renderer::begin()
	{
		beginBatch();
	}

	void Renderer::beginBatch()
	{
		mQuadVertexData.clear();
		mQuadIndexCount = 0;
		mQuadVertexCount = 0;
		mTextureSlotIndex = 1;
	}

	void Renderer::end()
	{
		if (mQuadVertexData.empty()) return;

		mQuadVB.setData(mQuadVertexData.size() * sizeof(meshes::QuadVertex), mQuadVertexData.data());

		mGLState.bindShader(mQuadShader);
		mGLState.bindVA(mQuadVA);
		glapi::drawIndexed(mQuadIndexCount);
		mStats.drawCalls++;
	}

	void Renderer::drawQuad(const Transform& tf, const glm::vec4& tint)
	{
		if (mQuadIndexCount >= sQuadIndicesPerDraw) 
			reset();

		glm::mat4 tfMatrix = tf.matrix();
		for (size_t i{ 0 }; i < 4; i++)
		{
			S2F_ASSERT((mQuadVertexCount + i) < mQuadVertexData.capacity(), "Vertex data indexing error in drawQuad")
			mQuadVertexData.emplace_back(
				tfMatrix * meshes::quadVertexPositions[i],
				tint,
				meshes::quadTextureCoords[i],
				0.f
			);
		}

		mQuadVertexCount += 4;
		mQuadIndexCount += 6;
		mStats.quadCount++;
	}

    void Renderer::drawQuad(const Transform &tf, const Texture &texture, const glm::vec4 &tint)
    {
		if (mQuadIndexCount >= sQuadIndicesPerDraw) 
			reset();

		GLuint texID = texture.id();
		f32 textureIndex{ 0.f };
		for (size_t i{ 1 }; i < mTextureSlotIndex; i++)
		{
			if (mTextureSlots[i] == texID)
			{
				textureIndex = (f32)i;
				break;
			}
		}

		if (textureIndex == 0.f)
		{
			if (mTextureSlotIndex >= mTextureSlots.size())
				reset();

			textureIndex = (f32)mTextureSlotIndex;
			mTextureSlots[mTextureSlotIndex] = texID;
			mTextureSlotIndex++;
		}

		glm::mat4 tfMatrix = tf.matrix();
		for (size_t i{ 0 }; i < 4; i++)
		{
			S2F_ASSERT((mQuadVertexCount + i) < mQuadVertexData.capacity(), "Vertex data indexing error in drawQuad")
			mQuadVertexData.emplace_back(
				tfMatrix * meshes::quadVertexPositions[i],
				tint,
				meshes::quadTextureCoords[i],
				textureIndex
			);
		}

		mQuadVertexCount += 4;
		mQuadIndexCount += 6;
		mStats.quadCount++;
    }

    void Renderer::reset()
	{
		end();
		beginBatch();
	}
}
