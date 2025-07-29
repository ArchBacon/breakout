#pragma once

#include <array>
#include <memory>

#include "breakout/levels/level.hpp"
#include "breakout/menu.hpp"
#include "breakout/objects/ball.hpp"
#include "breakout/objects/paddle.hpp"
#include "breakout/objects/player.hpp"
#include "core/engine.hpp"

namespace breakout
{
    class Gameplay final : public Level
    {
        std::array<std::shared_ptr<engine::Image>, 4> backgrounds
        {
            Engine.Renderer().CreateImage("assets/images/background_01.png"),
            Engine.Renderer().CreateImage("assets/images/background_02.png"),
            Engine.Renderer().CreateImage("assets/images/background_03.png"),
            Engine.Renderer().CreateImage("assets/images/background_04.png"),
        };
        int4 fieldPadding {16, 48, 16, 0}; // padding before reaching the play area

        Player player {};
        Paddle paddle {};
        std::vector<Ball> balls {};

    public:
        void BeginPlay() override;
        void Tick(float deltaTime) override;
        void Draw() override;

        void KeyPressed(const uint32_t key) override;

        [[nodiscard]] int GetStageBackgroundIndex() const;

        void CalculateBallStartDirection(Ball& ball) const;
    };
}
