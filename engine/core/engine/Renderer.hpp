#pragma once
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Buffer.hpp"
#include "GLAPI.hpp"
#include "GLState.hpp"
#include "meshes.hpp"
#include "transform.hpp"
#include "Texture.hpp"
#include "projview.hpp"

namespace s2f
{
	struct RendererStatistics
	{
		u32 drawCalls{ 0 };
		u32 quadCount{ 0 };
		u32 textureSlotsUsed{ 0 };
	};

	class Renderer
	{
	public:
		Renderer();
		~Renderer() = default;

		void init();

		void begin();
		void end();
		void drawQuad(const Transform& tf, const glm::vec4& color);
		void drawQuad(const Transform& tf, Texture* texture, const glm::vec4& tint = glm::vec4(1.f));

		void setProjview(const ProjViewData& projview) { mProjview = projview; }

		RendererStatistics frameStatistics() const { return mStats; }
		void resetStatistics() { mStats = {}; }

	private:
		void fillQuadBatchIndices();

		void beginBatch();
		void reset();

	private:
		GLState mGLState;
		ProjViewData mProjview;
		VertexArray mQuadVA;
		Buffer mQuadVB;
		Buffer mQuadIB;
		Shader mQuadShader;
		Layout mQuadVBLayout;

		static constexpr size_t sQuadsPerDraw{ 5000 };
		static constexpr size_t sQuadVerticesPerDraw{ 4 * sQuadsPerDraw };
		static constexpr size_t sQuadIndicesPerDraw{ 6 * sQuadsPerDraw };

		std::vector<u32> mQuadBatchIndices;
		std::vector<meshes::QuadVertex> mQuadVertexData;
		u32 mQuadVertexCount{ 0 };
		u32 mQuadIndexCount{ 0 };

		std::vector<Texture*> mTextures;
		u32 mTextureSlotIndex{ 1 };

		RendererStatistics mStats{};
	};
}
