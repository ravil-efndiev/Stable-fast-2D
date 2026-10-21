#pragma once
#include "style.hpp"

namespace s2f::ui
{
	struct Button
	{
		StyleSource style;
		std::string text;
		std::function<void()> onClick;
	};
}
