#pragma once

#include "core/core.hpp"
#include "rendering/font.hpp"

namespace breakout
{
    // Abstract class
    class PowerFont : public engine::Font
    {
    public:
        PowerFont(const std::string& file = "assets/images/power_default.png") : Font(
            file,
            8,
            1,
            "01234567"
        ) {}
    };

    class PowerBreakFont : public PowerFont
    {
    public:
        PowerBreakFont()
            : PowerFont("assets/images/power_break.png")
        {}
    };

    class PowerCatchFont : public PowerFont
    {
    public:
        PowerCatchFont()
            : PowerFont("assets/images/power_catch.png")
        {}
    };

    class PowerDisruptFont : public PowerFont
    {
    public:
        PowerDisruptFont()
            : PowerFont("assets/images/power_disrupt.png")
        {}
    };

    class PowerEnlargeFont : public PowerFont
    {
    public:
        PowerEnlargeFont()
            : PowerFont("assets/images/power_enlarge.png")
        {}
    };

    class PowerLaserFont : public PowerFont
    {
    public:
        PowerLaserFont()
            : PowerFont("assets/images/power_laser.png")
        {}
    };

    class PowerPlayerFont : public PowerFont
    {
    public:
        PowerPlayerFont()
            : PowerFont("assets/images/power_player.png")
        {}
    };

    class PowerSlowFont : public PowerFont
    {
    public:
        PowerSlowFont()
            : PowerFont("assets/images/power_slow.png")
        {}
    };
}
