#include "mainmenu.hpp"

#include "core/engine.hpp"

void breakout::MainMenu::BeginPlay()
{
    background = Engine.Renderer().CreateImage("assets/images/background_01.png");
}

void breakout::MainMenu::Draw()
{
    Engine.Renderer().Draw(background, {0, 32});
}
