#pragma once
#include "include.hpp"

namespace s2f
{
    struct FrameDataState
    {
        u64 frameCount{};
        f64 accumulatedTime{};
        f64 averageFPS{};
        f64 measureIntervalSeconds{ 1.f };
    };
}
