#pragma once

#include <memory>

namespace breakout
{
    class Window;
    class Audio;
    
    class Engine
    {
        std::unique_ptr<Window> window {nullptr};
        std::unique_ptr<Audio> audio {nullptr};
        
        bool running {true};

    public:
        void Initialize();
        void Run();
        void Shutdown();

        [[nodiscard]] Window& Window() const { return *window; }
        [[nodiscard]] Audio& Audio() const { return *audio; }
    };
}

extern breakout::Engine Engine;
