#pragma once
#include "api/math/Rect.hpp"

namespace s2f
{
    struct Collider
    {
        RectCenterF bounds;
        glm::vec2 offset{};
        bool isTrigger{ false };

        Collider(const glm::vec2& size, const glm::vec2& offset = glm::vec2(0.f))
            : offset(offset), bounds(offset, size) {}
    };

    struct ColliderList
    {
        std::vector<Collider> colliders;
    };
}

