#include "layout.hpp"

namespace s2f
{
	i32 getLayoutElementComponentCount(LayoutElementType type)
	{
		switch (type)
		{
			case LayoutElementType::Float: return 1;
			case LayoutElementType::Float2: return 2;
			case LayoutElementType::Float3: return 3;
			case LayoutElementType::Float4: return 4;
			case LayoutElementType::Float4x4: return 4;
		}
	}
}
