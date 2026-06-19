#include "transform.hpp"

namespace s2f
{
	glm::mat4 Transform::matrix() const
	{
		return useDegrees 
			? makeTransformDegreeRotations(position, rotation, scale) 
			: makeTransform(position, rotation, scale);
	}

	glm::mat4 makeTransform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& scale)
	{
		glm::mat4 matrix{ 1.f };

		matrix = glm::translate(matrix, position);
		matrix = glm::rotate(matrix, rotation.x, { 1.f, 0.f, 0.f });
		matrix = glm::rotate(matrix, rotation.y, { 0.f, 1.f, 0.f });
		matrix = glm::rotate(matrix, rotation.z, { 0.f, 0.f, 1.f });
		matrix = glm::scale(matrix, glm::vec3(scale, 0.f));

		return matrix;
	}

	glm::mat4 makeTransformDegreeRotations(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& scale)
	{
		glm::mat4 matrix{ 1.f };

		matrix = glm::translate(matrix, position);
		matrix = glm::rotate(matrix, glm::radians(rotation.x), { 1.f, 0.f, 0.f });
		matrix = glm::rotate(matrix, glm::radians(rotation.y), { 0.f, 1.f, 0.f });
		matrix = glm::rotate(matrix, glm::radians(rotation.z), { 0.f, 0.f, 1.f });
		matrix = glm::scale(matrix, glm::vec3(scale, 0.f));

		return matrix;
	}
}
