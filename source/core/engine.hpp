#pragma once

#include <SDL3/SDL.h>

namespace breakout
{
    class Engine
    {
        bool running {true};
        SDL_Window* window {nullptr};

    public:
        void Initialize();
        void Run();
        void Shutdown();
    };
}

extern breakout::Engine Engine;
