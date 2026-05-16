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
		mGLState.init();
		auto viewport = glapi::getViewportSize();
		mProjview = makeOrthoPojectionView({ 0.f, 0.f }, 0.f, 1.f, (f32)viewport.x / (f32)viewport.y);

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
				LayoutElement(LayoutElementType::Float4, offsetof(meshes::QuadVertex, position)),
				LayoutElement(LayoutElementType::Float4, offsetof(meshes::QuadVertex, tint)),
				LayoutElement(LayoutElementType::Float2, offsetof(meshes::QuadVertex, texCoord)),
				LayoutElement(LayoutElementType::Float,  offsetof(meshes::QuadVertex, texIndex))
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

		mTextures.resize(maxTexSlots);
		mQuadShader.setUniformIntArray("uTextures", maxTexSlots, texSlotIndices.data(), &mGLState);

		S2F_INFO_VERBOSE("Renderer: Initialized");
		S2F_INFO_VERBOSE("Renderer: Maximum GPU supported texture slots = " << maxTexSlots);
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
		mQuadShader.setUniformMat4("uProjview", mProjview.projection * mProjview.view, &mGLState);
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

		for (u32 i{ 1 }; i < mTextureSlotIndex; i++)
			mGLState.bindTexture(*mTextures[i], (u32)i);
		
		glapi::drawIndexed(mQuadIndexCount);
		mStats.drawCalls++;
	}

	void Renderer::drawQuad(const Transform& tf, const glm::vec4& color)
	{
		if (mQuadIndexCount >= sQuadIndicesPerDraw) 
			reset();

		glm::mat4 tfMatrix = tf.matrix();
		for (u32 i{ 0 }; i < 4; i++)
		{
			S2F_ASSERT((mQuadVertexCount + i) < mQuadVertexData.capacity(), "Vertex data indexing error in drawQuad")
			mQuadVertexData.emplace_back(
				tfMatrix * meshes::quadVertexPositions[i],
				color,
				meshes::quadTextureCoords[i],
				0.f
			);
		}

		mQuadVertexCount += 4;
		mQuadIndexCount += 6;
		mStats.quadCount++;
	}

    void Renderer::drawQuad(const Transform& tf, Texture* texture, const glm::vec4& tint)
    {
		if (mQuadIndexCount >= sQuadIndicesPerDraw) 
			reset();

		GLuint texID = texture->id();
		f32 textureIndex{ 0.f };
		for (u32 i{ 1 }; i < mTextureSlotIndex; i++)
		{
			if (mTextures[i]->id() == texID)
			{
				textureIndex = (f32)i;
				break;
			}
		}

		if (textureIndex == 0.f)
		{
			if (mTextureSlotIndex >= mTextures.size())
			{
				S2F_WARN("Texture slot limit reached for this batch, consider using sprite atlases");
				reset();
			}

			textureIndex = (f32)mTextureSlotIndex;
			mTextures[mTextureSlotIndex] = texture;
			mTextureSlotIndex++;
		}

		glm::mat4 tfMatrix = tf.matrix();
		for (u32 i{ 0 }; i < 4; i++)
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
