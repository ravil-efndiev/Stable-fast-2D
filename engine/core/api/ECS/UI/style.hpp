#pragma once
#include "include.hpp"

namespace s2f::ui
{
	struct Style
	{
		std::string fontName{ "default" };
		glm::vec4 color{ 1.f };
		glm::vec4 hoverColor{ 1.f };
		glm::vec4 clickColor{ 1.f };
		glm::vec4 backgroundColor{ 0.3f, 0.3f, 0.3f, 1.f };
		glm::vec4 backgroundHoverColor{ 0.4f, 0.4f, 0.4f, 1.f };
		glm::vec4 backgroundClickColor{ backgroundHoverColor };
		glm::vec2 padding{ 0.f };
	};

	using StyleSource = std::variant<std::string, Style>;
}
