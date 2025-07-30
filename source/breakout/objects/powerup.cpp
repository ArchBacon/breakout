#include "powerup.hpp"

#include "ball.hpp"
#include "player.hpp"

breakout::PowerUp::PowerUp()
{
    PopulateSprites<PowerFont>();
    bounds = {
        .left = 0,
        .top = 0,
        .right = static_cast<float>(sprites[0]->width),
        .bottom = static_cast<float>(sprites[0]->height)
    };
}

breakout::PowerUp::~PowerUp()
{
    if (!consumed)
    {
        OnEnd();
    }
}

void breakout::PowerUp::OnBegin()
{
    powerTimer.Reset();
    active = true;
    if (internalBeginCallback) internalBeginCallback();
    if (onBeginCallback) onBeginCallback();
}

void breakout::PowerUp::OnEnd()
{
    if (internalEndCallback) internalEndCallback();
    if (onEndCallback) onEndCallback();
    consumed = true;
}

void breakout::PowerUp::Update(const float deltaTime)
{
    location += direction * (speed * deltaTime);
    if (!consumed && active && powerTimer.Elapsed() >= duration)
    {
        OnEnd();
    }
}

void breakout::PowerUp::Animate()
{
    const float frameTime = 1.f / animationSpeed;
    if (animationTimer.Elapsed() >= frameTime)
    {
        animationIndex = (++animationIndex + (int)sprites.size()) % (int)sprites.size();
        animationTimer.Reset();
    }

    Engine.Renderer().Draw(sprites[animationIndex], location);
}

breakout::PowerExtraLife::PowerExtraLife(Player& player)
{
    PopulateSprites<PowerPlayerFont>();
    type = PowerUpType::ExtraLife;
    duration = 0.0f; // Instant
    internalBeginCallback = [&]()
    {
        player.extraLives++;
    };
}

breakout::PowerSlow::PowerSlow(std::vector<Ball>& balls)
{
    PopulateSprites<PowerSlowFont>();
    type = PowerUpType::Slow;
    duration = 5.0f;
    internalBeginCallback = [&]()
    {
        for (auto& ball : balls)
        {
            ball.speed = 325.f / 2.f; // Halve the speed
        } 
    };
    internalEndCallback = [&]()
    {
        for (auto& ball : balls)
        {
            ball.speed = 325.f; // Set back to original 
        } 
    };
}
