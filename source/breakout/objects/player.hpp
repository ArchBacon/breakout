#pragma once

#include <cstdint>

namespace breakout
{
    struct Player
    {
        uint8_t extraLives {2};
        bool alive {true};
        std::shared_ptr<engine::Image> lifeSprite
        {
            Engine.Renderer().CreateImage("assets/images/hp.png")
        };
    };
}
