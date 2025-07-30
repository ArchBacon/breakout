#pragma once

#include <cstdint>
#include <functional>
#include "rendering/image.hpp"

namespace breakout
{
    enum class LevelType
    {
        MainMenu,
        Settings,
        Controls,
        GamePlay,
        GameOver,
        GameEnd,
        Exit,
    };
    
    class Level
    {
        std::function<void(LevelType)> levelChangeCallback {};
        
    public:
        Level() = default;
        virtual ~Level() = default;

        Level(const Level& other) = delete;
        Level &operator=(const Level&) = delete;
        Level(Level&& other) = delete;
        Level& operator=(Level&& other) = delete;

        virtual void BeginPlay() {}
        virtual void Tick([[maybe_unused]] float deltaTime) {}
        virtual void Draw() {}
        virtual void Shutdown() {}
        
        virtual void KeyUp([[maybe_unused]] const uint32_t key) {}
        virtual void KeyDown([[maybe_unused]] const uint32_t key) {}
        virtual void KeyPressed([[maybe_unused]] const uint32_t key) {}

    public:
        /** +--------------------+ */
        /** + callback method is + */
        /** + Based on AI Answer + */
        /** +--------------------+ */
        void SetLevelChangeCallback(const std::function<void(LevelType)>& callback)
        {
            levelChangeCallback = callback;
        }

    protected:
        void RequestLevelChange(const LevelType newLevel) const
        {
            levelChangeCallback(newLevel);
        }
    };
}
