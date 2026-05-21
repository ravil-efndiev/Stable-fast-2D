#pragma once
#include "include.hpp"

namespace s2f
{
    struct Time
    {
        f64 currentTime{ 0.f };
        f64 lastTime{ 0.f };
        f64 deltaTime{ 0.f };
        f32 fixedDeltaTime{ 60.f };

	    void update(f64 currentTime);

        static Time get();
        static f32 current();
        static f32 delta();
        static f32 fixedDelta();
    };

}
