#pragma once

#include "rendering/font.hpp"

namespace breakout
{
    class OtherAltFont : public engine::Font
    {
    public:
        OtherAltFont() : Font(
            "assets/font/font_other_alt.png",
            26,
            2,
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ()/-+\"',.~?;:"
        ) {}
    };
}
