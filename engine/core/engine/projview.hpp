#pragma once
#include "include.hpp"

namespace s2f
{
	struct ProjViewData
	{
		glm::mat4 projection{ 1.f };
		glm::mat4 view{ 1.f };
	};

	ProjViewData makeOrthoPojectionView(const glm::vec2& position, f32 rotation, f32 zoom, f32 aspect);
}
