#include "powerup.hpp"

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

void breakout::PowerUp::OnBegin()
{
    powerTimer.Reset();
    active = true;
    if (internalBeginCallback) internalBeginCallback();
    if (onBeginCallback) onBeginCallback();
}

void breakout::PowerUp::OnEnd() const
{
    if (internalEndCallback) internalEndCallback();
    if (onEndCallback) onEndCallback();
}

void breakout::PowerUp::Update(const float deltaTime)
{
    location += direction * (speed * deltaTime);
    if (active && powerTimer.Elapsed() >= duration)
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
    duration = 0.0f; // Instant
    internalBeginCallback = [&]()
    {
        player.extraLives++;
    };
}
