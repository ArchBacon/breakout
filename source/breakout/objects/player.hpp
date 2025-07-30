#pragma once

#include <cstdint>

#include "rendering/image.hpp"
#include "core/engine.hpp"

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
