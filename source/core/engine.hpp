#pragma once

#include <memory>

namespace breakout
{
    class Window;
    class Audio;
    class Renderer;
    
    class Engine
    {
        std::unique_ptr<Window> window {nullptr};
        std::unique_ptr<Audio> audio {nullptr};
        std::unique_ptr<Renderer> renderer {nullptr};
        
        bool running {true};

    public:
        void Initialize();
        void Run();
        void Shutdown();

        [[nodiscard]] Window& Window() const { return *window; }
        [[nodiscard]] Audio& Audio() const { return *audio; }
        [[nodiscard]] Renderer& Renderer() const { return *renderer; }
    };
}

extern breakout::Engine Engine;
