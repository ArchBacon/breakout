#pragma once

#include "game.hpp"

namespace breakout
{
    class Breakout final : public engine::Game
    {
        engine::Image* background {nullptr};
        
    public:
        Breakout();

        void Initialize() override;
        void Draw() override;
        void Shutdown() override;
    };
}
