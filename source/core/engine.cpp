#include "engine.hpp"

#include <iostream>

breakout::Engine Engine;

namespace breakout
{
void Engine::Initialize()
{
}

void Engine::Run()
{
    while (running)
    {
        std::cout << "Hello World!\n";
    }
}

void Engine::Shutdown()
{
}

}
