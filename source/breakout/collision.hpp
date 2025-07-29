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

        [[nodiscard]] float2 Center() const;
        [[nodiscard]] bool Overlaps(const Bounds& other) const;
    };
}
