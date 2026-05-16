#pragma once
#include "include.hpp"

namespace s2f
{
	struct InputState
	{
		static constexpr u64 sMaxKeys{ 1024 };
		static constexpr u64 sMaxMouseButtons{ 8 };

		std::array<bool, sMaxKeys> keys{ false };
		std::array<bool, sMaxKeys> previousKeys{ false };

		std::array<bool, sMaxMouseButtons> mouseButtons{ false };
		std::array<bool, sMaxMouseButtons> previousMouseButtons{ false };
	};
}
