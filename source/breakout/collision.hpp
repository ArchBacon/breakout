#pragma once

#include "core/types.hpp"

namespace breakout
{
    struct Bounds
    {
        float left {0};
        float top {0};
        float right {0};
        float bottom {0};

        [[nodiscard]] float2 Min() const;
        [[nodiscard]] float2 Center() const;
        [[nodiscard]] float2 Max() const;

        static bool Overlap(const Bounds& srcBounds, float2 srcPos, const Bounds& other, float2 otherPos);
    };
}
