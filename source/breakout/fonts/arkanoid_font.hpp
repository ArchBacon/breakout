#pragma once

#include "rendering/font.hpp"

namespace breakout
{
    class ArkanoidFont : public engine::Font
    {
    public:
        ArkanoidFont() : Font(
            "assets/font/font_arkanoid.png",
            5,
            9,
            "ABCDEFGIJKLMNOPQRSTUVWXYZ0123456789.<>*/!?_ H"
        ) {}
    };
}
