#include "engine.hpp"

#include <chrono>
#include <SDL3/SDL_events.h>

#include "audio.hpp"
#include "window.hpp"
#include "rendering/image.hpp"
#include "rendering/renderer.hpp"

breakout::Engine Engine;

void breakout::Engine::Initialize()
{
    window = std::make_unique<breakout::Window>(448, 512, "Breakout", "assets/icon.bmp");
    audio = std::make_unique<breakout::Audio>();
    audio->SetVolume(0.05f); // Set volume to 5%
    renderer = std::make_unique<breakout::Renderer>();
}

void breakout::Engine::Run()
{
    auto previousTime = std::chrono::high_resolution_clock::now();
    SDL_Event event;

    Image* background = renderer->CreateImage("assets/images/background_01.png");

    while (running)
    {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        const float elapsed = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - previousTime).count());
        const float deltaTime = elapsed / 1000000.0f; // time in seconds
        previousTime = currentTime;

        while (SDL_PollEvent(&event))
        {
            // Exit engine on [X] button
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }

            // Exit engine when [ESC] is pressed
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)
            {
                running = false;
            }
        }

        renderer->BeginFrame();

        renderer->Draw(background, 0, 32);
        
        renderer->EndFrame();
    }
}

void breakout::Engine::Shutdown()
{
    SDL_Quit();
}
