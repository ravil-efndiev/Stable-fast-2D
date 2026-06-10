#pragma once
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Buffer.hpp"
#include "GLAPI.hpp"
#include "GLState.hpp"
#include "meshes.hpp"
#include "Texture.hpp"
#include "projview.hpp"
#include "SubTexture.hpp"

namespace s2f
{
	struct RendererInfo
	{
		RenderMode mode;
		u64 quadBatchSize;
	};

	struct RendererStatistics
	{
		u32 drawCalls{ 0 };
		u32 quadCount{ 0 };
		u32 textureSlotsUsed{ 0 };
	};

	class Renderer
	{
	public:
		Renderer(const RendererInfo& info);
		~Renderer() = default;

		void init();

		void begin();
		void end();
		void drawQuad(const glm::mat4& transform, const glm::vec4& color);
		void drawQuad(const glm::mat4& transform, Texture* texture, const glm::vec4& tint = glm::vec4(1.f));
		void drawQuad(
			const glm::mat4& transform, 
			Texture* texture, 
			const SubTexture& subTexture, 
			const glm::vec4& tint = glm::vec4(1.f)
		);
		void drawQuad(
			const glm::mat4& transform,
			Texture* texture,
			const std::array<glm::vec2, 4>& textureCoords,
			const glm::vec4& tint = glm::vec4(1.f)
		);

		void submitQuad(std::span<glm::mat4> transforms, const glm::vec4& tint = glm::vec4(1.f));
		void submitQuad(std::span<glm::mat4> transforms, Texture* texture, const glm::vec4& tint = glm::vec4(1.f));

		void setProjview(const ProjViewData& projview) { mProjview = projview; }
		void resetProjview();

		void setRenderMode(RenderMode mode) { mRenderMode = mode; }

		RendererStatistics frameStatistics() const { return mStats; }
		void resetStatistics() { mStats = {}; }

		GLState& glState() { return mGLState; }

	private:
		void fillQuadBatchIndices();

		void beginBatch();
		void reset();

		void createQuadBatchResources();
		void createQuadSingleResources();

	private:
		ProjViewData mProjview;
		GLState mGLState;
		Shader mBatchQuadShader;
		VertexArray mBatchQuadVA;
		Buffer mBatchQuadVB;
		Buffer mBatchQuadIB;

		Shader mQuadShader;
		VertexArray mQuadVA;
		Buffer mQuadVB;
		Buffer mQuadIB;
		Buffer mQuadInstanceVB;

		std::vector<u32> mQuadBatchIndices;
		std::vector<meshes::QuadBatchVertex> mQuadVertexData;
		u32 mQuadVertexCount{ 0 };
		u32 mQuadIndexCount{ 0 };

		const u64 mQuadBatchSize;
		const u64 mQuadVerticesPerDraw;
		const u64 mQuadIndicesPerDraw;
		u64 mInstanceBufferCapacity{ 256 * sizeof(glm::mat4) };

		std::vector<Texture*> mTextures;
		u32 mTextureSlotIndex{ 1 };

		RendererStatistics mStats{};
		RenderMode mRenderMode;
	};
}
