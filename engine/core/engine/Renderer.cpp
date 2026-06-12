#include "Renderer.hpp"

namespace s2f
{
	Renderer::Renderer(const RendererInfo& info) : 
		mQuadBatchSize(info.quadBatchSize),
		mQuadVerticesPerDraw(mQuadBatchSize * 4),
		mQuadIndicesPerDraw(mQuadBatchSize * 6),
		mRenderMode(info.mode)
	{
		mQuadBatchIndices.resize(mQuadIndicesPerDraw);
		mQuadVertexData.reserve(mQuadVerticesPerDraw);
	}

	void Renderer::init()
	{
		mGLState.init();
		resetProjview();

		createQuadBatchResources();
		createQuadSingleResources();

		auto maxTexSlots = glapi::getMaxTextureSlots();
		std::vector<i32> texSlotIndices(maxTexSlots);
		for (i32 i{}; i < maxTexSlots; i++)
			texSlotIndices[i] = i;

		mTextures.resize(maxTexSlots);
		mBatchQuadShader.setUniformIntArray("uTextures", maxTexSlots, texSlotIndices.data(), &mGLState);

		Logger::infoVerbose("Renderer: Initialized");
		Logger::infoVerbose("Renderer: Maximum GPU supported texture slots = {}", maxTexSlots);
	}

	void Renderer::createQuadBatchResources()
	{
		mBatchQuadVA.create();
		mBatchQuadVB.create(BufferType::Vertex, mQuadVerticesPerDraw, mQuadVerticesPerDraw * sizeof(meshes::QuadBatchVertex));

		fillQuadBatchIndices();
		createBufferFromCollection<u32>(mBatchQuadIB, BufferType::Index, mQuadBatchIndices);

		Layout quadVBLayout
		{
			{
				LayoutElement(LayoutElementType::Float4, offsetof(meshes::QuadBatchVertex, position)),
				LayoutElement(LayoutElementType::Float4, offsetof(meshes::QuadBatchVertex, tint)),
				LayoutElement(LayoutElementType::Float2, offsetof(meshes::QuadBatchVertex, texCoord)),
				LayoutElement(LayoutElementType::Float,  offsetof(meshes::QuadBatchVertex, texIndex))
			},
			sizeof(meshes::QuadBatchVertex)
		};

		mBatchQuadVA.addVertexBuffer(mBatchQuadVB, quadVBLayout, Divisor::PerVertex);
		mBatchQuadVA.setIndexBuffer(mBatchQuadIB);

		mBatchQuadShader.create(SHADER_PATH / "quadBatch.vert", SHADER_PATH / "quadBatch.frag");
	}

	void Renderer::createQuadSingleResources()
	{
		std::array<meshes::QuadVertex, 4> quadVertices
		{
			meshes::QuadVertex{ { -0.5f, -0.5f, 0.f, 1.f }, {0.f, 0.f} },
			meshes::QuadVertex{ {  0.5f, -0.5f, 0.f, 1.f }, {1.f, 0.f} },
			meshes::QuadVertex{ {  0.5f,  0.5f, 0.f, 1.f }, {1.f, 1.f} },
			meshes::QuadVertex{ { -0.5f,  0.5f, 0.f, 1.f }, {0.f, 1.f} },
		};

		mQuadVA.create();
		createBufferFromCollection<meshes::QuadVertex>(mQuadVB, BufferType::Vertex, quadVertices);
		createBufferFromCollection<u32>(mQuadIB, BufferType::Index, meshes::quadIndices);
		mQuadInstanceVB.create(BufferType::Vertex, 0, mInstanceBufferCapacity);

		Layout quadVBLayout
		{
			{
				LayoutElement(LayoutElementType::Float4, offsetof(meshes::QuadVertex, position)),
				LayoutElement(LayoutElementType::Float2, offsetof(meshes::QuadVertex, texCoord)),
			},
			sizeof(meshes::QuadVertex)
		};

		Layout quadInstanceLayout
		{
			{
				LayoutElement(LayoutElementType::Float4x4, offsetof(meshes::QuadInstanceVertex, transform)),
				LayoutElement(LayoutElementType::Float4,   offsetof(meshes::QuadInstanceVertex, tint)),
			},
			sizeof(meshes::QuadInstanceVertex)
		};

		mQuadVA.addVertexBuffer(mQuadVB, quadVBLayout, Divisor::PerVertex);
		mQuadVA.addVertexBuffer(mQuadInstanceVB, quadInstanceLayout, Divisor::PerInstnace);
		mQuadVA.setIndexBuffer(mQuadIB);
		
		mQuadShaderTex.create(SHADER_PATH / "quadInstancedTex.vert", SHADER_PATH / "quadInstancedTex.frag");
		mQuadShaderCol.create(SHADER_PATH / "quadInstancedCol.vert", SHADER_PATH / "quadInstancedCol.frag");
		mQuadShaderTex.setUniformInt("uTextureIndex", 0);
	}

	void Renderer::fillQuadBatchIndices()
	{
		size_t offset{ 0 };
		for (size_t i{}; i < mQuadIndicesPerDraw; i += 6)
		{
			for (size_t j{}; j < meshes::quadIndices.size(); ++j)
			{
				mQuadBatchIndices[i + j] = offset + meshes::quadIndices[j];
			}
			offset += 4;
		}
	}

	void Renderer::begin()
	{
		mBatchQuadShader.setUniformMat4("uProjview", mProjview.projection * mProjview.view, &mGLState);
		beginBatch();
	}

	void Renderer::beginBatch()
	{
		mQuadVertexData.clear();
		mQuadIndexCount = 0;
		mQuadVertexCount = 0;
		mTextureSlotIndex = 1;
		std::fill(mTextures.begin(), mTextures.end(), nullptr);
	}

	void Renderer::end()
	{
		if (mQuadVertexData.empty()) return;

		mBatchQuadVB.setData(mQuadVertexData.size() * sizeof(meshes::QuadBatchVertex), mQuadVertexData.data());

		mGLState.bindShader(mBatchQuadShader);
		mGLState.bindVA(mBatchQuadVA);

		for (u32 i{ 1 }; i < mTextureSlotIndex; i++)
			mGLState.bindTexture(*mTextures[i], (u32)i);

		glapi::drawIndexed(mQuadIndexCount, mRenderMode);
		mStats.drawCalls++;
	}

	void Renderer::drawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		if (mQuadIndexCount >= mQuadIndicesPerDraw)
			flushBatchAndReset();

		for (u32 i{}; i < 4; ++i)
		{
			S2F_ASSERT((mQuadVertexCount + i) < mQuadVertexData.capacity(), "Vertex data indexing error in drawQuad");
			mQuadVertexData.emplace_back(
				transform * meshes::quadVertexPositions[i],
				color,
				meshes::quadTextureCoords[i],
				0.f
			);
		}

		mQuadVertexCount += 4;
		mQuadIndexCount += 6;
		mStats.quadInBatchCount++;
	}

	void Renderer::drawQuad(const glm::mat4& transform, Texture* texture, const glm::vec4& tint)
	{
		drawQuad(transform, texture, meshes::quadTextureCoords, tint);
	}

	void Renderer::drawQuad(
		const glm::mat4& transform,
		Texture* texture,
		const SubTexture& subTexture,
		const glm::vec4& tint
	) {
		drawQuad(transform, texture, subTexture.textureCoords(), tint);
	}

	void Renderer::drawQuad(
		const glm::mat4& transform,
		Texture* texture,
		const std::array<glm::vec2, 4>& textureCoords,
		const glm::vec4& tint
	) {
		if (mQuadIndexCount >= mQuadIndicesPerDraw)
			flushBatchAndReset();

		GLuint texID = texture->id();
		f32 textureIndex{ 0.f };
		for (u32 i{ 1 }; i < mTextureSlotIndex; ++i)
		{
			if (mTextures[i] && mTextures[i]->id() == texID)
			{
				textureIndex = (f32)i;
				break;
			}
		}

		if (textureIndex == 0.f)
		{
			if (mTextureSlotIndex >= mTextures.size())
			{
				Logger::warn("Texture slot limit reached for this batch, consider using sprite atlases");
				flushBatchAndReset();
			}

			textureIndex = (f32)mTextureSlotIndex;
			mTextures[mTextureSlotIndex] = texture;
			mTextureSlotIndex++;
		}

		for (u32 i{}; i < 4; ++i)
		{
			S2F_ASSERT((mQuadVertexCount + i) < mQuadVertexData.capacity(), "Vertex data indexing error in drawQuad");
			mQuadVertexData.emplace_back(
				transform * meshes::quadVertexPositions[i],
				tint,
				textureCoords[i],
				textureIndex
			);
		}

		mQuadVertexCount += 4;
		mQuadIndexCount += 6;
		mStats.quadInBatchCount++;
	}

	void Renderer::submitQuads(std::span<meshes::QuadInstanceVertex> instanceVertices)
	{
		submitQuads(instanceVertices, nullptr);
	}

	void Renderer::submitQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		meshes::QuadInstanceVertex instance{ transform, color };
		submitQuads(std::span(&instance, 1), nullptr);
	}

	void Renderer::submitQuad(const glm::mat4& transform, const glm::vec4& color, Texture* texture)
	{
		meshes::QuadInstanceVertex instance{ transform, color };
		submitQuads(std::span(&instance, 1), texture);
	}

	void Renderer::submitQuads(std::span<glm::mat4> transforms, std::span<glm::vec4> colors)
	{
		auto instanceVec = makeQuadInstanceVector(transforms, colors);
		submitQuads(instanceVec, nullptr);
	}

	void Renderer::submitQuads(std::span<glm::mat4> transforms, std::span<glm::vec4> colors, Texture* texture)
	{
		auto instanceVec = makeQuadInstanceVector(transforms, colors);
		submitQuads(instanceVec, texture);
	}

	void Renderer::submitQuads(std::span<meshes::QuadInstanceVertex> instanceVertices, Texture* texture)
	{
		mGLState.bindVA(mQuadVA);

		auto instanceVerticesBytes = instanceVertices.size_bytes();
		if (instanceVerticesBytes > mInstanceBufferCapacity)
		{
			mInstanceBufferCapacity *= 2;
			mQuadInstanceVB.realloc(mInstanceBufferCapacity);
		}
		mQuadInstanceVB.setData(instanceVerticesBytes, instanceVertices.data());

		if (texture)
		{
			mGLState.bindShader(mQuadShaderTex);
			mQuadShaderTex.setUniformMat4("uProjview", mProjview.projection * mProjview.view, &mGLState);
			mGLState.bindTexture(*texture, 0);
		}
		else
		{
			mGLState.bindShader(mQuadShaderCol);
			mQuadShaderCol.setUniformMat4("uProjview", mProjview.projection * mProjview.view, &mGLState);
		}

		glapi::drawIndexedInstanced(mQuadVA.indexBufferIndexCount(), instanceVertices.size(), mRenderMode);
		mStats.drawCalls++;
	}

    void Renderer::resetProjview()
	{
		auto viewport = glapi::getViewportSize();
		mProjview = makeOrthoPojectionView({ 0.f, 0.f }, 0.f, 1.f, (f32)viewport.x / (f32)viewport.y);
	}

    void Renderer::flushBatchAndReset()
	{
		end();
		beginBatch();
	}

	std::vector<meshes::QuadInstanceVertex> Renderer::makeQuadInstanceVector(
		std::span<glm::mat4> transforms,
		std::span<glm::vec4> colors
	) {
		auto tfSize = transforms.size();
		if (tfSize != colors.size())
		{
			Logger::error("makeQuadInstanceVector() transforms collection size must be same as colors");
			return {};
		}

		std::vector<meshes::QuadInstanceVertex> zipped;
		zipped.reserve(tfSize);

		for (size_t i{}; i < tfSize; ++i)
		{
			zipped.emplace_back(transforms[i], colors[i]);
		}
		return zipped;
	}
}
