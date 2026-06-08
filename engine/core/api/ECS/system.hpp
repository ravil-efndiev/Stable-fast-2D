#pragma once
#include "include.hpp"

namespace s2f
{
	class Entity;

	using System = std::function<void(const std::vector<Entity>&, f32 deltaTime)>;

}
