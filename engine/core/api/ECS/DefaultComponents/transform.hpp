#pragma once
#include "include.hpp"

namespace s2f
{
	struct Transform
	{
		glm::vec3 position{ 0.f };
		glm::vec3 rotation{ 0.f };
		glm::vec3 scale{ 1.f };

		glm::mat4 matrix() const;
	};

	glm::mat4 makeTransform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
}
