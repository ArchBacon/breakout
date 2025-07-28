#include "engine.hpp"

#include <chrono>
#include <iostream>
#include <SDL3/SDL.h>

breakout::Engine Engine;

void breakout::Engine::Initialize()
{
    // Initialize SDL3
    SDL_Init(SDL_INIT_VIDEO);

    // Create Window
    constexpr SDL_WindowFlags windowFlags = SDL_WINDOW_OPENGL;
    window = SDL_CreateWindow("Breakout", 448, 512, windowFlags);

    // Add icon to window
    SDL_Surface* iconSurface = SDL_LoadBMP("assets/icon.bmp");
    SDL_SetWindowIcon(window, iconSurface);
    SDL_DestroySurface(iconSurface);
}

void breakout::Engine::Run()
{
    auto previousTime = std::chrono::high_resolution_clock::now();
    SDL_Event event;

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
    }
}

void breakout::Engine::Shutdown()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}
