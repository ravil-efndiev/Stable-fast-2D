#pragma once
#include "include.hpp"

namespace s2f 
{
    // enum value represents attribute count
    enum class LayoutElementType : u8
    {
        Float = 1,
        Vec2  = 2,
        Vec3  = 3,
        Vec4  = 4,
        Mat4  = 4, // 4 Vec4 attributes
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
}
