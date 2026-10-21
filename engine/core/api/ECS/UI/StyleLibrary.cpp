#include "StyleLibrary.hpp"

namespace s2f::ui
{
	void StyleLibrary::addStyle(std::string_view name, const Style& style)
	{
		mStyles.emplace(name, style);
	}

	Style* StyleLibrary::getStyle(const std::string& name)
	{
		auto it = mStyles.find(name);
		if (it != mStyles.end())
			return &it->second;
		return nullptr;
	}
}
