#pragma once

#include "core/gamestate.hpp"

namespace breakout
{
    class BreakoutGameState : public engine::GameState
    {
    public:
        bool firstTimeOnMainMenu {true};
        uint32_t score {0};
        uint8_t stage {1};
    };
}
