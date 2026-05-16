#include "projview.hpp"

namespace s2f
{
	ProjViewData makeOrthoPojectionView(const glm::vec2& position, f32 rotation, f32 zoom, f32 aspect)
	{
		ProjViewData data{};
		data.projection = glm::ortho(-aspect * zoom, aspect * zoom, -zoom, zoom, -1.f, 1.f);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.f));
		transform = glm::rotate(transform, rotation, glm::vec3(0, 0, 1));
		data.view = glm::inverse(transform);
		return data;
	}
}
