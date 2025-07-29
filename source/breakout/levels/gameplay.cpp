#include "gameplay.hpp"

#include "core/engine.hpp"

void breakout::Gameplay::BeginPlay()
{
    background = Engine.Renderer().CreateImage("assets/images/background_01.png");
}

void breakout::Gameplay::Draw()
{
    Engine.Renderer().Draw(background, {0, 32});
}
