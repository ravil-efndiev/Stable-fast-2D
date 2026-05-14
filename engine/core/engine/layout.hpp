#pragma once
#include "include.hpp"

namespace s2f 
{
    enum class LayoutElementType : u8
    {
        Float,
        Float2,
        Float3,
        Float4,
        Float4x4
    };

    struct LayoutElement
    {
        u32 offset{ 0 };
        LayoutElementType type = LayoutElementType::Float;
        bool normalized = false;
        
        LayoutElement(LayoutElementType type, u32 offset, bool normalized = false)
			: type(type), offset(offset), normalized(normalized) { }
    };

    struct Layout
    {
        std::vector<LayoutElement> elements;
        size_t stride{ 0 };
	};

	i32 getLayoutElementComponentCount(LayoutElementType type);
}
