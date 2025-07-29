#pragma once

#include "game.hpp"
#include "level.hpp"

namespace breakout
{
    class Level;

    class Breakout final : public engine::Game
    {
        std::unique_ptr<Level> level {nullptr};
        
    public:
        Breakout();
        
        void BeginPlay() override { level->BeginPlay(); }
        void Tick(const float deltaTime) override { level->Tick(deltaTime); }
        void Draw() override { level->Draw(); }
        void Shutdown() override { level->Shutdown(); }

        void KeyUp(const uint32_t key) override { level->KeyUp(key); }
        void KeyDown(const uint32_t key) override { level->KeyDown(key); }
        void KeyPressed(const uint32_t key) override { level->KeyPressed(key); }
        
        void ChangeLevel(LevelType newLevelType);
    };
}
