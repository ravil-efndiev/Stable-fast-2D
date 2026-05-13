#pragma once
#include "include.hpp"

namespace s2f
{
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		glm::mat4 matrix() const;
	};
}