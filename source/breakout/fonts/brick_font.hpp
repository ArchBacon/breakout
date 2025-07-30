#pragma once

#include "rendering/font.hpp"

namespace breakout
{
    class BrickFont : public engine::Font
    {
    public:
        BrickFont() : Font(
            "assets/images/bricks.png",
            10,
            1,
            "0123456789"
        ) {}
    };
}
