#pragma once
#include "include.hpp"

namespace s2f
{
    struct Time
    {
        f64 currentTime{ 0.f };
        f64 lastTime{ 0.f };
        f64 deltaTime{ 0.f };
        f64 fixedDeltaTime{ 60.f };
    };

	void updateTime(Time& time, f64 currentTime);
}
