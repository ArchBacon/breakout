#include "collision.hpp"

float2 breakout::Bounds::Min() const
{
    return {left, top};
}

float2 breakout::Bounds::Center() const
{
    return {
        left + ((right - left) / 2),
        top + ((bottom - top) / 2),
    };
}

float2 breakout::Bounds::Max() const
{
    return {
        left + (right - left),
        top + (bottom - top),
    };
}

bool breakout::Bounds::Overlap(
    const Bounds& srcBounds,
    const float2 srcPos,
    const Bounds& other,
    const float2 otherPos
) {
    return (srcBounds.left + srcPos.x) < (other.right + otherPos.x)
        && (srcBounds.right + srcPos.x) > (other.left + otherPos.x)
        && (srcBounds.top + srcPos.y) < (other.bottom + otherPos.y)
        && (srcBounds.bottom + srcPos.y) > (other.top + otherPos.y);
}
