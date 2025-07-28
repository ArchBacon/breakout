#pragma once

#include <cstdint>
#include <iostream>
#include <string>

#include "rendering/image.hpp"
#include "rendering/renderer.hpp"

namespace engine
{
    struct GameConfig
    {
        std::string app_name {"Unnamed"};
        std::string app_icon {""};
        uint32_t window_width {800};
        uint32_t window_height {600};
    };
    
    class Game
    {
    public:
        GameConfig config {};
        
    public:
        virtual ~Game() = default;
        
        // Lifecycle
        virtual void Initialize() { std::cerr << "No game specified.\n"; }
        virtual void Tick(float deltaTime) {}
        virtual void Draw() {}
        virtual void Shutdown() {}

        // Input
        virtual void KeyUp(const uint32_t key) {}
        virtual void KeyDown(const uint32_t key) {}
        virtual void KeyPressed(const uint32_t key) {}

        virtual void ButtonUp(const uint32_t button) {}
        virtual void ButtonDown(const uint32_t button) {}
        virtual void ButtonPressed(const uint32_t button) {}

        virtual void MouseMove(const uint32_t x, const uint32_t y) {}
        virtual void MouseWheel(const float y) {}
    };
}
