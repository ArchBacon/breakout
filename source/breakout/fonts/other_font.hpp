#pragma once

#include "rendering/font.hpp"

namespace breakout
{
    class OtherFont : public engine::Font
    {
    public:
        OtherFont() : Font(
            "assets/font/font_other.png",
            26,
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ()/-+\"',.~?;:"
        ) {}
    };
}
