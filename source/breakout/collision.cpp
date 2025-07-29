#include "collision.hpp"

float2 breakout::Bounds::Center() const
{
    return {
        left + ((right - left) / 2),
        top + ((bottom - top) / 2),
    };
}

bool breakout::Bounds::Overlaps(const Bounds& other) const
{
    return left > other.left
        && right < other.right
        && top > other.top
        && bottom < other.bottom;
}
