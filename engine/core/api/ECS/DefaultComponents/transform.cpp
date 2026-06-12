#include "transform.hpp"

namespace s2f
{
	glm::mat4 Transform::matrix() const
	{
		return makeTransform(position, rotation, scale);
	}

	glm::mat4 makeTransform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	{
		glm::mat4 matrix{ 1.f };

		matrix = glm::translate(matrix, position);
		matrix = glm::rotate(matrix, rotation.x, { 1.f, 0.f, 0.f });
		matrix = glm::rotate(matrix, rotation.y, { 0.f, 1.f, 0.f });
		matrix = glm::rotate(matrix, rotation.z, { 0.f, 0.f, 1.f });
		matrix = glm::scale(matrix, scale);

		return matrix;
	}
}
