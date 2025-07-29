#include "gameplay.hpp"

#include "breakout/breakout_gamestate.hpp"
#include "core/audio.hpp"
#include "core/engine.hpp"

void breakout::Gameplay::BeginPlay()
{
    // TODO: Load bricks from stage file

    paddle.location = {
        Engine.Window().Width() / 2 - paddle.sprites[1]->width / 2,
        464
    };
    Ball ball {};
    ball.isAttachedToPaddle = true;
    ball.relAttachlocation = {
        paddle.sprites[1]->width / 2 - ball.sprites[1]->width / 2,
        0
    };
    balls.push_back(ball);

    Engine.Audio().Play("assets/audio/round_start.wav");
}

void breakout::Gameplay::Tick(const float deltaTime)
{
    // Update player location
    paddle.Update(deltaTime);
    paddle.location.x = glm::clamp(
        paddle.location.x,
        static_cast<float>(fieldPadding.x),
        static_cast<float>(Engine.Window().Width() - fieldPadding.z - paddle.sprites[1]->width)
    );

    // Update ball location
    for (auto& ball : balls)
    {
        ball.Update(deltaTime);

        if (ball.isAttachedToPaddle)
        {
            // Update ball location
            ball.location = ball.relAttachlocation
                + paddle.location
                - float2 {0.0f, ball.sprites[1]->height};

            // Update ball direction
            CalculateBallStartDirection(ball);
        }
    }

    // TODO: Handle collision and bounces
}

void breakout::Gameplay::Draw()
{
    // Draw background
    Engine.Renderer().Draw(backgrounds[GetStageBackgroundIndex()], {0, 32});

    // Draw ball(s)
    for (auto& ball : balls)
    {
        Engine.Renderer().Draw(ball.sprites, ball.location);

        // Draw the ball's direction when attached to the paddle
        if (ball.isAttachedToPaddle)
        {
            float2 start = ball.location + ball.bounds.Center();
            float2 end = start + (ball.direction * 60.f);
            Engine.Renderer().DrawLine(start, end, {255, 255, 255});
        }
    }

    // Draw remaining extra lives
    for (uint8_t i = 0; i < player.extraLives; i++)
    {
        Engine.Renderer().Draw(player.lifeSprite,
        {
           fieldPadding.x + (player.lifeSprite->width * i),
           Engine.Window().Height() - player.lifeSprite->height
        });
    }

    // Draw paddle
    Engine.Renderer().Draw(paddle.sprites, paddle.location);
}

void breakout::Gameplay::KeyPressed(const uint32_t key)
{
    // Move paddle
    if (key == SDLK_A || key == SDLK_LEFT)
    {
        paddle.direction = {-1, 0};
    }
    if (key == SDLK_D || key == SDLK_RIGHT)
    {
        paddle.direction = {1, 0};
    }

    // Shoot
    if (key == SDLK_W || key == SDLK_UP || key == SDLK_SPACE)
    {
        for (auto& ball : balls)
        {
            ball.isAttachedToPaddle = false;
        }
    }
}

int breakout::Gameplay::GetStageBackgroundIndex() const
{
    const uint8_t stage = Engine.GameState<BreakoutGameState>().stage;
    return (stage - 1) % static_cast<uint8_t>(backgrounds.size());
}

void breakout::Gameplay::CalculateBallStartDirection(Ball& ball) const
{
    const float paddleCenter = (paddle.location + paddle.bounds.Center()).x;
    const float screenCenter = static_cast<float>(Engine.Window().Width()) / 2.0f;

    // Normalize paddle location to screenspace (between -1 and 1)
    const float playableWidth = static_cast<float>(Engine.Window().Width() - fieldPadding.x - fieldPadding.z);
    const float paddleOffset = (paddleCenter - screenCenter) / (playableWidth / 2);

    // Angle between 75 and -75 degrees
    const float angle = glm::radians(paddleOffset * 75);
    ball.direction = {glm::sin(angle), -glm::cos(angle)};
}
