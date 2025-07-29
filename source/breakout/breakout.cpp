#include "breakout.hpp"

#include "breakout_gamestate.hpp"
#include "level.hpp"
#include "core/audio.hpp"
#include "core/engine.hpp"
#include "levels/controls.hpp"
#include "levels/gameplay.hpp"

#include "levels/mainmenu.hpp"
#include "levels/settings.hpp"

breakout::Breakout::Breakout()
{
    // Configure window properties
    Engine.Window().SetIcon("assets/icon.bmp");
    Engine.Window().SetTitle("Breakout");
    Engine.Window().SetSize(448, 512);

    // Change clear color
    Engine.Renderer().SetClearColor({0, 0, 0});

    // Lower default volume
    Engine.Audio().SetVolume(0.2f);

    // Update game state to store variables over app lifetime
    Engine.SetGameState<BreakoutGameState>();

    level = std::make_unique<MainMenu>();
    level->SetLevelChangeCallback([&](const LevelType type) { ChangeLevel(type); });
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
        level = std::make_unique<Settings>();
        break;
    case LevelType::Controls:
        level = std::make_unique<Controls>();
        break;
    case LevelType::GamePlay:
        level = std::make_unique<Gameplay>();
        break;
    case LevelType::GameOver:
        LogGame->Warn("GameOver not implemented. Exiting...");
        return;
    case LevelType::GameEnd:
        LogGame->Warn("GameEnd not implemented. Exiting...");
        return;
    case LevelType::Exit:
        Engine.Shutdown();
        return;
    default:;
    }

    level->SetLevelChangeCallback([&](const LevelType type) { ChangeLevel(type); });
    level->BeginPlay();
}
