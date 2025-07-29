#pragma once

#include <cstdint>
#include <iostream>
#include <string>

#include "core/logger.hpp"
#include "rendering/image.hpp"
#include "rendering/renderer.hpp"
#include "core/core.hpp"
#include "core/types.hpp"

namespace engine
{
    class Game
    {
    public:
        virtual ~Game() = default;
        
        // Lifecycle
        virtual void BeginPlay() {}
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
