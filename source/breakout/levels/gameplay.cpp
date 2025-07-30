#include "gameplay.hpp"

#include "breakout/breakout_gamestate.hpp"
#include "breakout/fonts/other_font.hpp"
#include "breakout/fonts/other_font_alt.hpp"
#include "core/audio.hpp"
#include "core/engine.hpp"
#include "core/string_helper.hpp"

void breakout::Gameplay::BeginPlay()
{
    GetBricksFromStage(
        Engine.GameState<BreakoutGameState>().stage,
        fieldBounds,
        bricks,
        bricksToClear
    );

    stageText = Engine.GetFont<OtherFont>()->CreateText("Stage");
    stage = Engine.GetFont<OtherAltFont>()->CreateText(ZeroFill(Engine.GameState<BreakoutGameState>().stage, 2));
    scoreText = Engine.GetFont<OtherFont>()->CreateText("Score");
    score = Engine.GetFont<OtherAltFont>()->CreateText(ZeroFill((int)Engine.GameState<BreakoutGameState>().score, 5));
    livesText = Engine.GetFont<OtherFont>()->CreateText("Lives");
    lives = Engine.GetFont<OtherAltFont>()->CreateText(ZeroFill(player.extraLives, 2));

    paddle.location = {
        static_cast<float>(Engine.Window().Width()) / 2.f - paddle.bounds.Max().x / 2,
        464
    };
    
    Ball ball {};
    ball.isAttachedToPaddle = true;
    ball.relAttachlocation = {
        paddle.bounds.Max().x / 2 - ball.bounds.Max().x / 2,
        0
    };
    balls.push_back(ball);

    Engine.Audio().Play("assets/audio/round_start.wav");
}

void breakout::Gameplay::Tick(const float deltaTime)
{
    if (!player.alive) return;
    
    // Update player location
    paddle.Update(deltaTime);
    paddle.location.x = glm::clamp(
        paddle.location.x,
        static_cast<float>(fieldPadding.x),
        static_cast<float>(Engine.Window().Width() - fieldPadding.z) - paddle.bounds.Max().x
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
                - float2 {0.0f, ball.bounds.Max().y};

            // Update ball direction
            CalculateBallStartDirection(ball);
        }
    }

    // TODO: Handle collision and bounces
    HandleBallWallBounces();
    HandleBallPaddleBounces();
}

void breakout::Gameplay::Draw()
{
    // Draw background
    Engine.Renderer().Draw(backgrounds[GetStageBackgroundIndex()], {0, 32});

    // Draw score and stage
    Engine.Renderer().Draw(stageText, {Engine.Window().Width() / 6 - stageText->width / 2, 6});
    Engine.Renderer().Draw(stage, {Engine.Window().Width() / 6 - stage->width / 2, 18});
    
    Engine.Renderer().Draw(scoreText, {Engine.Window().Width() / 2 - scoreText->width / 2, 6});
    Engine.Renderer().Draw(score, {Engine.Window().Width() / 2 - score->width / 2, 18});
    
    Engine.Renderer().Draw(livesText, {Engine.Window().Width() / 6 * 5 - stageText->width / 2, 6});
    Engine.Renderer().Draw(lives, {Engine.Window().Width() / 6 * 5 - stage->width / 2, 18});

    // Draw bricks
    for (const auto& brick : bricks)
    {
        Engine.Renderer().Draw(brick->sprite, brick->location);
    } 
    
    // Draw ball(s)
    for (auto& ball : balls)
    {
        // Draw the ball's direction when attached to the paddle
        if (ball.isAttachedToPaddle)
        {
            const float2 start = ball.location + ball.bounds.Center();
            const float2 end = start + (ball.direction * 60.f);
            Engine.Renderer().DrawLine(start, end, {255, 255, 255});
        }

        Engine.Renderer().Draw(ball.sprites, ball.location);
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
    const uint8_t currentStage = Engine.GameState<BreakoutGameState>().stage;
    return (currentStage - 1) % static_cast<uint8_t>(backgrounds.size());
}

void breakout::Gameplay::OnGameEnded()
{
    Engine.Audio().Play("assets/audio/game_over.wav");
}

void breakout::Gameplay::CalculateBallStartDirection(Ball& ball) const
{
    /** +--------------------+ */
    /** + Based on AI Answer + */
    /** +--------------------+ */
    
    const float paddleCenter = (paddle.location + paddle.bounds.Center()).x;
    const float screenCenter = static_cast<float>(Engine.Window().Width()) / 2.0f;

    // Normalize paddle location to screenspace (between -1 and 1)
    const float playableWidth = static_cast<float>(Engine.Window().Width() - fieldPadding.x - fieldPadding.z);
    const float paddleOffset = (paddleCenter - screenCenter) / (playableWidth / 2);

    // Angle between 75 and -75 degrees
    const float angle = glm::radians(paddleOffset * ballPaddleMaxStartAngle);
    ball.direction = {glm::sin(angle), -glm::cos(angle)};
}

void breakout::Gameplay::HandleBallLost(const Ball& ball)
{
    Engine.Audio().Play("assets/audio/arkanoid_ball_lost.wav");
    
    // Remove the current ball
    std::erase_if(balls, [&](const Ball& b) { return &b == &ball; });
    
    // If there are still balls in play, continue playing
    if (!balls.empty())
    {
        return;
    }
    
    // If the player has no extra lives, end the game
    if (player.extraLives == 0)
    {
        player.alive = false;
        OnGameEnded();
        return;
    }

    // Update lives
    player.extraLives--;
    lives = Engine.GetFont<OtherAltFont>()->CreateText(ZeroFill(player.extraLives, 2));
    
    // Reset ball to paddle
    Ball newBall {};
    newBall.isAttachedToPaddle = true;
    newBall.relAttachlocation = {
        paddle.bounds.Max().x / 2 - newBall.bounds.Max().x / 2,
        0
    };
    balls.push_back(newBall);
}

void breakout::Gameplay::HandleBallWallBounces()
{
    for (auto& ball : balls)
    {
        // Left wall
        if (ball.bounds.Min().x + ball.location.x <= fieldBounds.left)
        {
            ball.location.x = fieldBounds.left;
            ball.direction.x = -ball.direction.x;
            Engine.Audio().Play("assets/audio/arkanoid_hit.wav");
            return;
        }

        // Right wall
        if (ball.bounds.Max().x + ball.location.x >= fieldBounds.right)
        {
            ball.location.x = fieldBounds.right - ball.bounds.Max().x;
            ball.direction.x = -ball.direction.x;
            Engine.Audio().Play("assets/audio/arkanoid_hit.wav");
            return;
        }

        // Top wall
        if (ball.bounds.Min().y + ball.location.y <= fieldBounds.top)
        {
            ball.location.y = fieldBounds.top;
            ball.direction.y = -ball.direction.y;
            Engine.Audio().Play("assets/audio/arkanoid_hit.wav");
            return;
        }

        // Bottom wall
        if (ball.bounds.Min().y + ball.location.y >= fieldBounds.bottom)
        {
            // ball.location.y = fieldBounds.bottom - ball.bounds.Max().y;
            // ball.direction.y = -ball.direction.y;
            // Engine.Audio().Play("assets/audio/arkanoid_hit.wav");
            // return;
            
            HandleBallLost(ball);
            return;
        }
    } 
}

void breakout::Gameplay::HandleBallPaddleBounces()
{
    for (auto& ball : balls)
    {
        if (ball.isAttachedToPaddle) continue;
        
        if (Bounds::Overlap(ball.bounds, ball.location, paddle.bounds, paddle.location))
        {
            /** +--------------------+ */
            /** + Based on AI Answer + */
            /** +--------------------+ */
            
            // Bounce the ball upward
            ball.direction.y = -abs(ball.direction.y);
        
            // Calculate new X direction based on where ball hit the paddle
            float paddleCenter = paddle.location.x + paddle.bounds.Max().x / 2.0f;
            float ballCenter = ball.location.x + ball.bounds.Max().x / 2.0f;
            float offset = (ballCenter - paddleCenter) / (paddle.bounds.Max().x / 2.0f);
        
            // Apply angle based on hit position (clamp offset to [-1, 1])
            offset = glm::max(-1.0f, glm::min(1.0f, offset));
            const float angle = offset * glm::radians(ballPaddleMaxBounceAngle);
        
            ball.direction = {sin(angle), -cos(angle)};
        
            // Move ball above paddle to prevent sticking
            ball.location.y = paddle.location.y - ball.bounds.Max().y;

            Engine.Audio().Play("assets/audio/arkanoid_hit.wav");
        }
    } 
}
