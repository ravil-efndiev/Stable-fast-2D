#pragma once
#include "style.hpp"

namespace s2f::ui
{
	class StyleLibrary
	{
	public:
		void addStyle(std::string_view name, const Style& style);
		Style* getStyle(const std::string& name);

	private:
		std::unordered_map<std::string, Style> mStyles;
	};
}
