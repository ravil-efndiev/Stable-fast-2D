#pragma once
#include "include.hpp"

namespace s2f
{
	namespace meshes
	{
		struct QuadVertex
		{
			glm::vec4 position{ 0.f };
			glm::vec4 tint{ 0.f };
			glm::vec2 texCoord{ 0.f };
			f32 texIndex{ 0.f };
		};

		static std::array<glm::vec4, 4> quadVertexPositions
		{
			glm::vec4( 0.5f,  0.5f, 0.0f, 1.f),
			glm::vec4( 0.5f, -0.5f, 0.0f, 1.f),
			glm::vec4(-0.5f, -0.5f, 0.0f, 1.f),
			glm::vec4(-0.5f,  0.5f, 0.0f, 1.f)
		};
		
		static std::array<glm::vec2, 4> quadTextureCoords
		{
			glm::vec2(1.f, 1.f),
			glm::vec2(1.f, 0.f),
			glm::vec2(0.f, 0.f),
			glm::vec2(0.f, 1.f)
		};

		static std::array<u32, 6> quadIndices
		{
			0, 1, 3,
			1, 2, 3
		};

	}
}
