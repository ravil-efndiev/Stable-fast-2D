#pragma once
#include "include.hpp"

namespace s2f
{
	class Entity;

	using SystemFunc = std::function<void(const std::vector<Entity>&, f32 deltaTime)>;

	enum class SystemType : u8
	{
		Normal, FixedTime
	};

	struct System
	{
		SystemFunc func;
		SystemId id;
		SystemType type;

		void operator()(const std::vector<Entity>& entities, f32 deltaTime)
		{
			func(entities, deltaTime);
		}
	};
}
