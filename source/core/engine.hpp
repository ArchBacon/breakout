#pragma once

namespace breakout
{
    
class Engine
{
    bool running = true;
    
public:
    void Initialize();
    void Run();
    void Shutdown();
};
    
}

extern breakout::Engine Engine;