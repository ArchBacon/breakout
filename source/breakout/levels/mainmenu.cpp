#include "mainmenu.hpp"

#include "breakout/arkanoid_font.hpp"
#include "core/audio.hpp"
#include "core/engine.hpp"

void breakout::MainMenu::BeginPlay()
{
    background = Engine.Renderer().CreateImage("assets/images/mainmenu.png");
    helloWorld = Engine.GetFont<ArkanoidFont>()->CreateText("Hello World!");

    Engine.Audio().Play("assets/audio/game_start.wav");
}

void breakout::MainMenu::Draw()
{
    Engine.Renderer().Draw(background, {0, 0});
    Engine.Renderer().Draw(helloWorld, {104, 226});
}
