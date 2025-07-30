#pragma once

#include <array>
#include <memory>

#include "breakout/levels/level.hpp"
#include "breakout/menu.hpp"
#include "breakout/objects/ball.hpp"
#include "breakout/objects/brick.hpp"
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
        std::vector<Brick*> bricks {};
        int bricksToClear {0};
        
        std::shared_ptr<engine::Image> scoreText {nullptr};
        std::shared_ptr<engine::Image> score {nullptr};
        std::shared_ptr<engine::Image> stageText {nullptr};
        std::shared_ptr<engine::Image> stage {nullptr};
        std::shared_ptr<engine::Image> livesText {nullptr};
        std::shared_ptr<engine::Image> lives {nullptr};

        float ballPaddleMaxStartAngle = 75.f;
        float ballPaddleMaxBounceAngle = 60.f;
        
        int4 fieldPadding {16, 48, 16, 0}; // padding before reaching the play area
        Bounds fieldBounds
        {
            .left = 16,
            .top = 48,
            .right = static_cast<float>(Engine.Window().Width() - 16),
            .bottom = static_cast<float>(Engine.Window().Height()),
        };

        Player player {};
        Paddle paddle {};
        std::vector<Ball> balls {};

    public:
        void BeginPlay() override;
        void Tick(float deltaTime) override;
        void Draw() override;

        void KeyDown(uint32_t key) override;
        void KeyPressed(uint32_t key) override;

        [[nodiscard]] int GetStageBackgroundIndex() const;

        void OnGameEnded();
        void ReloadStage();
        void NextStage();
        void PrevStage();
        
        void CalculateBallStartDirection(Ball& ball) const;
        void HandleBallLost(const Ball& ball);
        void HandleBallWallBounces();
        void HandleBallPaddleBounces();
        void HandleBallBrickBounces();
    };
}
