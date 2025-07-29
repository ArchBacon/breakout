#include "mainmenu.hpp"

#include "core/audio.hpp"
#include "core/engine.hpp"

void breakout::MainMenu::BeginPlay()
{
    background = Engine.Renderer().CreateImage("assets/images/mainmenu.png");

    Engine.Audio().Play("assets/audio/game_start.wav");
}

void breakout::MainMenu::Draw()
{
    Engine.Renderer().Draw(background, {0, 32});
}
