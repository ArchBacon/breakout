#include "breakout.hpp"

#include "level.hpp"
#include "core/audio.hpp"
#include "core/engine.hpp"

#include "levels/mainmenu.hpp"

breakout::Breakout::Breakout()
{
    // Configure window properties
    Engine.Window().SetIcon("assets/icon.bmp");
    Engine.Window().SetTitle("Breakout");
    Engine.Window().SetSize(448, 512);

    // Change clear color
    Engine.Renderer().SetClearColor({0, 0, 0});

    // Lower default volume
    Engine.Audio().SetVolume(0.05f);

    ChangeLevel(LevelType::MainMenu);
}

void breakout::Breakout::ChangeLevel(const LevelType newLevelType)
{
    if (level)
    {
        level->Shutdown();
    }

    switch (newLevelType)
    {
    case LevelType::MainMenu:
        level = std::make_unique<MainMenu>();
        break;
    case LevelType::Settings:
        LogGame->Warn("Settings not implemented. Exiting...");
        Engine.Shutdown();
        break;
    case LevelType::Controls:
        LogGame->Warn("Controls not implemented. Exiting...");
        Engine.Shutdown();
        break;
    case LevelType::GamePlay:
        LogGame->Warn("GamePlay not implemented. Exiting...");
        Engine.Shutdown();
        break;
    case LevelType::GameOver:
        LogGame->Warn("GameOver not implemented. Exiting...");
        Engine.Shutdown();
        break;
    case LevelType::GameEnd:
        LogGame->Warn("GameEnd not implemented. Exiting...");
        Engine.Shutdown();
        break;
    case LevelType::Exit:
        Engine.Shutdown();
        break;
    default:;
    }

    level->SetLevelChangeCallback([&](const LevelType type) { ChangeLevel(type); });
    level->BeginPlay();
}
