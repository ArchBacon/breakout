#include "mainmenu.hpp"

#include "breakout/arkanoid_font.hpp"
#include "core/audio.hpp"
#include "core/engine.hpp"


void breakout::MainMenu::BeginPlay()
{
    LogGame->Info("MainMenu::BeginPlay()");
    
    background = Engine.Renderer().CreateImage("assets/images/mainmenu.png");
    
    menu.pointer = Engine.GetFont<ArkanoidFont>()->CreateText(">");
    menu.buttons.emplace_back(
        Engine.GetFont<ArkanoidFont>()->CreateText("Start Game"),
        [&]() { RequestLevelChange(LevelType::GamePlay); }
    );
    menu.buttons.emplace_back(
        Engine.GetFont<ArkanoidFont>()->CreateText("Controls"),
        [&]() { RequestLevelChange(LevelType::Controls); }
    );
    menu.buttons.emplace_back(
        Engine.GetFont<ArkanoidFont>()->CreateText("Settings"),
        [&]() { RequestLevelChange(LevelType::Settings); }
    );
    menu.buttons.emplace_back(
        Engine.GetFont<ArkanoidFont>()->CreateText("Exit"),
        [&]() { RequestLevelChange(LevelType::Exit); }
    );
    menu.cycle = false;
    
    Engine.Audio().Play("assets/audio/game_start.wav");
}

void breakout::MainMenu::Draw()
{
    Engine.Renderer().Draw(background, {0, 0});

    menu.Draw({104, 226}, 36);
}

void breakout::MainMenu::KeyDown(const uint32_t key)
{
    if (key == SDLK_S || key == SDLK_DOWN)
    {
        menu.Next();
    }
    if (key == SDLK_W || key == SDLK_UP)
    {
        menu.Prev();
    }

    if (key == SDLK_SPACE || key == SDLK_RETURN)
    {
        menu.Click();
    }
}
