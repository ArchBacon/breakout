#pragma once

#include <memory>

namespace breakout
{
    class Window;
    
    class Engine
    {
        std::unique_ptr<Window> window {nullptr};
        
        bool running {true};

    public:
        void Initialize();
        void Run();
        void Shutdown();

        [[nodiscard]] Window& Window() const { return *window; }
    };
}

extern breakout::Engine Engine;
