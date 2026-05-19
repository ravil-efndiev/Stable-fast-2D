#pragma once
#include "engine/projview.hpp"

namespace s2f
{
	struct Camera
	{
		glm::vec2 position;
		f32 zoom;
		f32 rotation;
		
		Camera(const glm::vec2& position = glm::vec2(0.f, 0.f), f32 zoom = 1.f, f32 rotation = 0.f);

		ProjViewData projview() const;
	};
}
