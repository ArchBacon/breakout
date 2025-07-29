#pragma once

#include "core/gamestate.hpp"

namespace breakout
{
    class BreakoutGameState : public engine::GameState
    {
    public:
        bool firstTimeOnMainMenu = true;        
    };
}
