#pragma once

#include "game.hpp"
#include "objects/ball.hpp"
#include "objects/paddle.hpp"
#include "objects/player.hpp"

namespace breakout
{
    class Breakout final : public engine::Game
    {
        Player player {};
        Paddle paddle {};
        std::vector<Ball> balls {};

    public:
        Breakout();
        
        void BeginPlay() override;
        void Tick(float deltaTime) override;
        void Draw() override;
        void Shutdown() override {}

        void KeyUp(const uint32_t key) override {}
        void KeyDown(const uint32_t key) override {}
        void KeyPressed(const uint32_t key) override;
    };
}
