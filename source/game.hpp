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
        virtual void Tick([[maybe_unused]] float deltaTime) {}
        virtual void Draw() {}
        virtual void Shutdown() {}

        // Input
        virtual void KeyUp([[maybe_unused]] const uint32_t key) {}
        virtual void KeyDown([[maybe_unused]] const uint32_t key) {}
        virtual void KeyPressed([[maybe_unused]] const uint32_t key) {}

        virtual void ButtonUp([[maybe_unused]] const uint32_t button) {}
        virtual void ButtonDown([[maybe_unused]] const uint32_t button) {}
        virtual void ButtonPressed([[maybe_unused]] const uint32_t button) {}

        virtual void MouseMove([[maybe_unused]] const uint32_t x, [[maybe_unused]] const uint32_t y) {}
        virtual void MouseWheel([[maybe_unused]] const float y) {}
    };
}
