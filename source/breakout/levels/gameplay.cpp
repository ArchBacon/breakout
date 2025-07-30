#include "gameplay.hpp"

#include "breakout/breakout_gamestate.hpp"
#include "breakout/fonts/other_font.hpp"
#include "breakout/fonts/other_font_alt.hpp"
#include "core/audio.hpp"
#include "core/engine.hpp"
#include "core/string_helper.hpp"

void breakout::Gameplay::BeginPlay()
{
    GetBricksFromStage(Engine.GameState<BreakoutGameState>().stage, fieldBounds, bricks, bricksToClear);

    gameOverText = Engine.GetFont<ArkanoidFont>()->CreateText("Game Over");
    gameEndText = Engine.GetFont<ArkanoidFont>()->CreateText("Victory");
    overlay = Engine.Renderer().CreateImage("assets/images/dark_overlay.png");
    textLoc = {
        Engine.Window().Width() / 2 - gameOverText->width / 2,
        Engine.Window().Height()
    };
    textEndLoc = {
        Engine.Window().Width() / 2 - gameOverText->width / 2,
        Engine.Window().Height() / 3 * 2
    };
    scoreEndHeight = Engine.Window().Height() / 2;

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
    if (!player.alive || gameCompleted)
    {
        scoreHeight += textSpeed * deltaTime;
        scoreHeight = glm::min(scoreHeight, scoreEndHeight);
        
        textLoc.y -= textSpeed * deltaTime;
        textLoc.y = glm::max(textLoc.y, textEndLoc.y);
        
        return;
    }

    for (const auto& powerup : powerups)
    {
        if (powerup->active || powerup->consumed) continue;
        powerup->Update(deltaTime);
    } 
    
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

    HandleBallWallBounces();
    HandleBallPaddleBounces();
    HandleBallBrickBounces();
    HandlePowerUpPaddlePickups();
}

void breakout::Gameplay::Draw()
{
    // Draw background
    Engine.Renderer().Draw(backgrounds[GetStageBackgroundIndex()], {0, 32});

    // Draw lives and stage
    Engine.Renderer().Draw(stageText, {Engine.Window().Width() / 6 - stageText->width / 2, 6});
    Engine.Renderer().Draw(stage, {Engine.Window().Width() / 6 - stage->width / 2, 18});
    
    Engine.Renderer().Draw(livesText, {Engine.Window().Width() / 6 * 5 - stageText->width / 2, 6});
    Engine.Renderer().Draw(lives, {Engine.Window().Width() / 6 * 5 - stage->width / 2, 18});

    // Draw bricks
    for (const auto& brick : bricks)
    {
        Engine.Renderer().Draw(brick->sprite, brick->location);
    }

    // Draw power ups
    for (const auto& powerup : powerups)
    {
        if (powerup->active || powerup->consumed) continue;
        powerup->Animate();
        Engine.Renderer().Draw(powerup->shadow, powerup->location);
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

    if (!player.alive)
    {
        Engine.Renderer().Draw(overlay, {0, 0});
        Engine.Renderer().Draw(gameOverText, textLoc);
    }

    if (gameCompleted)
    {
        Engine.Renderer().Draw(overlay, {0, 0});
        Engine.Renderer().Draw(gameEndText, textLoc);
    }

    // draw score
    Engine.Renderer().Draw(scoreText, {Engine.Window().Width() / 2 - scoreText->width / 2, scoreHeight - 12});
    Engine.Renderer().Draw(score, {Engine.Window().Width() / 2 - score->width / 2, scoreHeight});
}

void breakout::Gameplay::KeyDown(const uint32_t key)
{
#ifdef _DEBUG
    // Cycle levels
    if (key == SDLK_RIGHTBRACKET)
    {
        NextStage();
    }
    if (key == SDLK_LEFTBRACKET)
    {
        PrevStage();
    }
#endif

    if (!player.alive || gameCompleted || key == SDLK_ESCAPE)
    {
        Engine.Audio().Play("assets/audio/pickup1.wav");
        RequestLevelChange(LevelType::MainMenu);
    }

    // Shoot
    if (key == SDLK_W || key == SDLK_UP || key == SDLK_SPACE || key == SDLK_RETURN)
    {
        for (auto& ball : balls)
        {
            ball.isAttachedToPaddle = false;
        }
    }
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

void breakout::Gameplay::ReloadStage()
{
    powerups.clear();
    
    // Reset balls
    balls.clear();
    Ball ball {};
    ball.isAttachedToPaddle = true;
    ball.relAttachlocation = {
        paddle.bounds.Max().x / 2 - ball.bounds.Max().x / 2,
        0
    };
    balls.push_back(ball);

    // Populate bricks
    GetBricksFromStage(Engine.GameState<BreakoutGameState>().stage, fieldBounds, bricks, bricksToClear);

    // Update sprites
    stage = Engine.GetFont<OtherAltFont>()->CreateText(ZeroFill(Engine.GameState<BreakoutGameState>().stage, 2));

    // Reset player position
    paddle.location = {
        static_cast<float>(Engine.Window().Width()) / 2.f - paddle.bounds.Max().x / 2,
        464
    };

    // Play Start level sound
    Engine.Audio().Play("assets/audio/round_start.wav");
}

void breakout::Gameplay::NextStage()
{
    auto& stageRef = Engine.GameState<BreakoutGameState>().stage;
    if (stageRef == stageCount)
    {
        gameCompleted = true;
        textLoc = {
            Engine.Window().Width() / 2 - gameEndText->width / 2,
            Engine.Window().Height()
        };
        textEndLoc = {
            Engine.Window().Width() / 2 - gameEndText->width / 2,
            Engine.Window().Height() / 3 * 2
        };
        return;
    }
    
    stageRef = glm::min(++stageRef, stageCount);
    
    ReloadStage();
}

void breakout::Gameplay::PrevStage()
{
    auto& stageRef = Engine.GameState<BreakoutGameState>().stage;
    stageRef = static_cast<uint8_t>(glm::max(stageRef - 1, 1));
    ReloadStage();
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
        if (ball.isAttachedToPaddle) continue;
        
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

void breakout::Gameplay::HandlePowerUpPaddlePickups()
{
    for (const auto& powerup : powerups)
    {
        if (powerup->active || powerup->consumed) continue; // No need to check for bounds, it's not in the level
        if (Bounds::Overlap(powerup->bounds, powerup->location, paddle.bounds, paddle.location))
        {
            // Look for all currently active powers to deactivate the current active ones
            for (const auto& pwr : powerups)
            {
                if (pwr->active && !pwr->consumed)
                {
                    pwr->OnEnd();
                }
            } 

            // Pick up the new power
            Engine.GameState<BreakoutGameState>().score += powerup->score;
            score = Engine.GetFont<OtherAltFont>()->CreateText(ZeroFill((int)Engine.GameState<BreakoutGameState>().score, 5));
            powerup->OnBegin();

            Engine.Audio().Play("assets/audio/powerup.wav");
        }
    }
}

/** +--------------------+ */
/** + Based on AI Answer + */
/** + I don't like this  + */
/** + But it works...    + */
/** +--------------------+ */
void breakout::Gameplay::HandleBallBrickBounces()
{
    for (auto& ball : balls)
    {
        if (ball.isAttachedToPaddle) continue;
        
        auto hitBrickIt = bricks.end();
    
        // Find the first brick that collides with the ball
        for (auto it = bricks.begin(); it != bricks.end(); ++it)
        {
            if (Bounds::Overlap(ball.bounds, ball.location, (*it)->bounds, (*it)->location))
            {
                hitBrickIt = it;
                
                // Calculate actual bounds for overlap calculation
                const float4 brickBounds = {
                    static_cast<float>((*it)->location.x),
                    static_cast<float>((*it)->location.y),
                    static_cast<float>((*it)->location.x + BrickData.bricksize.x),
                    static_cast<float>((*it)->location.y + BrickData.bricksize.y)
                };
                
                const float4 ballBounds = {
                    ball.location.x,
                    ball.location.y,
                    ball.location.x + ball.bounds.Max().x,
                    ball.location.y + ball.bounds.Max().y
                };
                
                // Calculate overlaps
                float overlapLeft = ballBounds.z - brickBounds.x;   // ball right - brick left
                float overlapRight = brickBounds.z - ballBounds.x;  // brick right - ball left
                float overlapTop = ballBounds.w - brickBounds.y;    // ball bottom - brick top
                float overlapBottom = brickBounds.w - ballBounds.y; // brick bottom - ball top
                
                float minOverlap = std::min(std::min(overlapLeft, overlapRight), 
                                          std::min(overlapTop, overlapBottom));
                
                // Determine collision side and bounce
                if (minOverlap == overlapLeft || minOverlap == overlapRight) {
                    ball.direction.x = -ball.direction.x;
                    // Move ball out of collision zone
                    if (minOverlap == overlapLeft) {
                        ball.location.x = brickBounds.x - ball.bounds.Max().x - 1.0f;
                    } else {
                        ball.location.x = brickBounds.z + 1.0f;
                    }
                } else {
                    ball.direction.y = -ball.direction.y;
                    // Move ball out of collision zone
                    if (minOverlap == overlapTop) {
                        ball.location.y = brickBounds.y - ball.bounds.Max().y - 1.0f;
                    } else {
                        ball.location.y = brickBounds.w + 1.0f;
                    }
                }
                
                break;
            }
        }
        
        // Handle the hit brick if one was found
        if (hitBrickIt != bricks.end())
        {
            const auto& hitBrick = *hitBrickIt;
            
            hitBrick->health--;
            if (hitBrick->health == 0)
            {
                SpawnPowerUp(hitBrick->droppedPowerUp, hitBrick->location);
                
                Engine.GameState<BreakoutGameState>().score += hitBrick->score;
                score = Engine.GetFont<OtherAltFont>()->CreateText(ZeroFill((int)Engine.GameState<BreakoutGameState>().score, 5));
                bricksToClear--;
                
                // Remove brick (unique_ptr handles deletion automatically)
                bricks.erase(hitBrickIt);
                
                if (bricksToClear <= 0)
                {
                    NextStage();
                }
            }

            Engine.Audio().Play("assets/audio/arkanoid_hit.wav");
        }
    }
}

void breakout::Gameplay::SpawnPowerUp(const PowerUpType type, const int2 location)
{
    std::unique_ptr<PowerUp> power = nullptr;
    
    switch (type)
    {
    case PowerUpType::ExtraLife:
        power = std::make_unique<PowerExtraLife>(player);
        power->onBeginCallback = [&]() { lives = Engine.GetFont<OtherAltFont>()->CreateText(ZeroFill(player.extraLives, 2)); };
        break;
    case PowerUpType::Slow:
        power = std::make_unique<PowerSlow>(balls);
        break;
    case PowerUpType::None:
    case PowerUpType::MAX__:
        return;
    }
    
    power->location = location;
    powerups.push_back(std::move(power));
}
