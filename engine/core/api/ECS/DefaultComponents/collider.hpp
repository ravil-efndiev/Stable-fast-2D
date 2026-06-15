#pragma once
#include "api/math/Rect.hpp"

namespace s2f
{
    struct Collider
    {
        RectF bounds;
        bool isTrigger{ false };
    };
}
